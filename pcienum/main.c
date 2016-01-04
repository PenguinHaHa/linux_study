//
//This program is used to test Linux user space vs kernel space
// It will try to enumerate PCI bus by accessing pci config space directly
//

#include <stdio.h>
#include <sys/io.h>

#define PCI_CONFIG_ADDR(bus, dev, fun, reg)   (1 << 31 | bus << 16 | dev << 11 | fun << 8 | reg)

int pciread(int bus, int dev, int fun, int reg);

int main (int argc, char* argv[])
{
  int bus, dev, fun;
  int regval;
  int i;

  iopl(3);
  //for (bus = 0; bus < 256; bus++)
  for (bus = 0; bus < 1; bus++)
  {
    for (dev = 0; dev < 32; dev++)
    {
      for (fun = 0; fun < 8; fun++)
      {
        regval = pciread(bus, dev, fun, 0);
        if (regval == 0xFFFFFFFF)
          continue;

        printf("%d.%d.%d : ", bus, dev, fun);
        for (i = 0; i < 10; i++)
          printf("%d:%08X|", i, pciread(bus, dev, fun, i*4));

        printf("\n");

      }
    }
  }
}

int pciread(int bus, int dev, int fun, int reg)
{
  outl_p(PCI_CONFIG_ADDR(bus, dev, fun, reg), 0xCF8);
  return inl_p(0xCFC);
}
