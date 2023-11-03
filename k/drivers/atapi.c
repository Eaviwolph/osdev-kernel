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
    inb(ATA_REG_STATUS(drive));
    inb(ATA_REG_STATUS(drive));
    inb(ATA_REG_STATUS(drive));
    inb(ATA_REG_STATUS(drive));
}

void select_drive(u16 bus, u8 slave)
{
    outb(ATA_REG_DRIVE(bus), (slave << 4));
}

short is_atapi_drive(u16 bus, u8 slave)
{
    select_drive(bus, slave);
    outb(ATA_REG_COMMAND(bus), IDENTIFY_PACKET_DEVICE);
    u8 status = inb(ATA_REG_STATUS(bus));
    if (status == 0)
        return 0;
    return 1;
}

u16 sreg = PRIMARY_REG;
u16 sdrive = ATA_PORT_SLAVE;

void discover_atapi_drive()
{
    /* Select current drive */
    select_drive(ATA_REG_DRIVE(sreg), sdrive);

    /* Wait 400ns for drive select to complete */
    ata_io_wait(sreg);

    /* Look for ATAPI signature */
    u8 sig[4];
    sig[0] = inb(ATA_REG_SECTOR_COUNT(sreg));
    sig[1] = inb(ATA_REG_LBA_LO(sreg));
    sig[2] = inb(ATA_REG_LBA_MI(sreg));
    sig[3] = inb(ATA_REG_LBA_HI(sreg));

    /* If it matches, it's an ATAPI drive */
    if (sig[0] == ATAPI_SIG_SC && sig[1] == ATAPI_SIG_LBA_LO && sig[2] == ATAPI_SIG_LBA_MI && sig[3] == ATAPI_SIG_LBA_HI)
    {
        printf("ATAPI drive found on bus %d, drive %d\r\n", sreg, sdrive);
        return;
    }
    else
    {
        printf("ATAPI drive not found on bus %x, drive %x\r\n", sreg, sdrive);
    }
}
