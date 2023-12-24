#include "../io.h"
#include <k/atapi.h>
#include <stdio.h>

static u16 sreg = SECONDARY_REG;
static u16 sdrive = ATA_PORT_SLAVE;

void busy_wait(u16 drive)
{
    while (inb(ATA_REG_STATUS(drive)) & BSY)
        ;
}

void wait_device_selection(u16 drive)
{
    while (!(inb(ATA_REG_STATUS(drive)) & RDY))
        ;
}

void wait_packet_request(u16 drive)
{
    while (1)
    {
        int status = inb(ATA_REG_STATUS(drive));
        if (!(status & BSY) && (status & DRQ))
            break;
    }
}

void ata_io_wait(u16 drive)
{
    inb(PRIMARY_DCR + drive);
    inb(PRIMARY_DCR + drive);
    inb(PRIMARY_DCR + drive);
    inb(PRIMARY_DCR + drive);
}

void select_drive(u16 bus, u8 slave)
{
    outb(ATA_REG_DRIVE(bus), 0xA0 & (slave << 4));
}

short is_atapi_drive(u16 bus, u8 slave)
{
    u8 sig[4];

    /* Select drive */
    select_drive(bus, slave);

    /* Wait for drive to be ready */
    ata_io_wait(bus);

    /* Send identify packet command */
    outb(ATA_REG_COMMAND(bus), IDENTIFY_PACKET_DEVICE);

    /* Wait for drive to be ready */
    ata_io_wait(bus);

    /* Read signature */
    sig[0] = inb(ATA_REG_SECTOR_COUNT(bus));
    sig[1] = inb(ATA_REG_LBA_LO(bus));
    sig[2] = inb(ATA_REG_LBA_MI(bus));
    sig[3] = inb(ATA_REG_LBA_HI(bus));

    /* Check if signature matches */
    if (sig[0] == ATAPI_SIG_SC && sig[1] == ATAPI_SIG_LBA_LO && sig[2] == ATAPI_SIG_LBA_MI && sig[3] == ATAPI_SIG_LBA_HI)
    {
        return 1;
    }

    return 0;
}

void discover_atapi_drive()
{
    outb(PRIMARY_DCR, INTERRUPT_DISABLE);
    outb(SECONDARY_DCR, INTERRUPT_DISABLE);
    outb(PRIMARY_DCR, SRST);
    outb(SECONDARY_DCR, SRST);

    u16 regs[2] = {PRIMARY_REG, SECONDARY_REG};
    u8 drives[2] = {ATA_PORT_MASTER, ATA_PORT_SLAVE};

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (is_atapi_drive(regs[i], drives[j]))
            {
                printf("Found ATAPI drive on bus %x and drive %x\r\n", regs[i], drives[j]);
                sreg = regs[i];
                sdrive = drives[j];
                break;
            }
        }
    }
}

void send_packet(struct SCSI_packet *pkt, u16 drive)
{
    busy_wait(drive);
    outb(ATA_REG_FEATURES(drive), 0);
    outb(ATA_REG_SECTOR_COUNT(drive), 0);
    outb(ATA_REG_LBA_MI(drive), CD_BLOCK_SZ);
    outb(ATA_REG_LBA_HI(drive), CD_BLOCK_SZ >> 8);
    outb(ATA_REG_COMMAND(drive), PACKET);

    ata_io_wait(drive);
    busy_wait(drive);
    wait_packet_request(drive);

    for (u16 *i = pkt; i < pkt + 1; i++)
    {
        outw(ATA_REG_DATA(drive), *i);
    }

    while (inb(ATA_REG_SECTOR_COUNT(drive)) & PACKET_DATA_TRANSMIT)
        ;
}

void read_block(size_t lba, u16 *buffer, size_t size)
{
    struct SCSI_packet pkt;
    pkt.control = 0;
    pkt.flags_hi = 0;
    pkt.transfer_length_lo = 1;
    pkt.transfer_length_milo = 0;
    pkt.transfer_length_mihi = 0;
    pkt.transfer_length_hi = 0;
    pkt.lba_lo = lba & 0xFF;
    pkt.lba_milo = (lba >> 8) & 0xFF;
    pkt.lba_mihi = (lba >> 16) & 0xFF;
    pkt.lba_hi = (lba >> 24) & 0xFF;
    pkt.flags_lo = 0;
    pkt.op_code = READ_12;

    printf("Sending packet\r\n");
    send_packet(&pkt, sdrive);
    printf("Packet sent\r\n");

    for (u16 i = 0; i < size; i++)
    {
        printf("Reading data\r\n");
        /* Wait until data is ready */
        wait_packet_request(sdrive);
        printf("Data ready\r\n");
        buffer[i] = inw(ATA_REG_DATA(sdrive));

        printf("Data read\r\n");
        /* Wait until data is transmitted */
        while (inb(ATA_REG_SECTOR_COUNT(sdrive)) & PACKET_COMMAND_COMPLETE)
            ;
        printf("Data transmitted\r\n");
    }
}

void init_atapi()
{
    discover_atapi_drive();
}