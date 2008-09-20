/* Abflussrohr */

Initialize:
  SetAction ("Still");
  return (1);

Imu:
  ExtractLiquid (0, -1);
  ExtractLiquid (0, -2);
  ExtractLiquid (0, 0);
  ExtractLiquid (0, 1);
  ExtractLiquid (0, 2);
  ExtractLiquid (0, 1);
  ExtractLiquid (0, 0);
  ExtractLiquid (0, -1);
  ExtractLiquid (0, -2);
  ExtractLiquid (0, -1);
  ExtractLiquid (0, 0);
  ExtractLiquid (0, 1);
  ExtractLiquid (0, 2);
  ExtractLiquid (0, 1);
  ExtractLiquid (0, -1);
  ExtractLiquid (0, -2);
  ExtractLiquid (0, -1);
  ExtractLiquid (0, 0);
  ExtractLiquid (0, 1);
  ExtractLiquid (0, 2);
  ExtractLiquid (0, 1);
  ExtractLiquid (0, 0);
  return (1);

Still:
  SetAction ("Still");
  return (1);

NuuNuu:
  SetAction ("Drain");
  return (1);