#include <k/atapi.h>
#include <stdio.h>
#include "../io.h"

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
    while (!(inb(ATA_REG_STATUS(drive)) & DRQ))
        ;
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

u16 sreg = SECONDARY_REG;
u16 sdrive = ATA_PORT_SLAVE;

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
