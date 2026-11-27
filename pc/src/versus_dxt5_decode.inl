// Expands DXT5 color and interpolated alpha blocks into 32-bit ARGB pixels.
void DecompressDXT5(const DWORD *Src, INT Width, INT Height, DWORD *Dest)
{
    INT BlockW = Min(4, Width);
    INT BlockH = Min(4, Height);
    DWORD *End = Dest + Width * Height;
    const DWORD *In = Src;
    DWORD *Block = Dest;
    for (INT by = 0; by < Max(Height / 4, 1); by++)
    {
        for (INT bx = 0; bx < Max(Width / 4, 1); bx++)
        {
            DWORD AlphaLo = In[0];
            DWORD AlphaHi = In[1];
            DWORD Colors  = In[2];
            DWORD Indices = In[3];
            In += 4;

            DWORD A0 = AlphaLo & 0xff;
            DWORD A1 = (AlphaLo >> 8) & 0xff;
            DWORD Alpha[8];
            DWORD Color[4];
            if (A0 > A1)
            {
                Alpha[2] = ((6 * A0 + 1 * A1) / 7) << 24;
                Alpha[3] = ((5 * A0 + 2 * A1) / 7) << 24;
                Alpha[4] = ((4 * A0 + 3 * A1) / 7) << 24;
                Alpha[5] = ((3 * A0 + 4 * A1) / 7) << 24;
                Alpha[6] = ((2 * A0 + 5 * A1) / 7) << 24;
                Alpha[7] = ((1 * A0 + 6 * A1) / 7) << 24;
            }
            else
            {
                Alpha[2] = ((4 * A0 + 1 * A1) / 5) << 24;
                Alpha[3] = ((3 * A0 + 2 * A1) / 5) << 24;
                Alpha[4] = ((2 * A0 + 3 * A1) / 5) << 24;
                Alpha[5] = ((1 * A0 + 4 * A1) / 5) << 24;
                Alpha[6] = 0;
                Alpha[7] = 0xff000000;
            }
            Alpha[0] = A0 << 24;
            Alpha[1] = A1 << 24;

            // Expand the two RGB565 end points to 8 bits per channel, in place.
            DWORD R0 = (((Colors & 0xf800) << 5) | (Colors & 0xe000)) << 3;
            DWORD G0 = ((Colors & 0x07e0) << 5) | ((Colors >> 1) & 0x300);
            DWORD B0 = ((Colors & 0x001f) << 3) | ((Colors >> 2) & 0x7);
            DWORD R1 = ((Colors & 0xf8000000) | ((Colors >> 5) & 0x7000000)) >> 8;
            DWORD G1 = (((Colors >> 6) & 0x180000) | (Colors & 0x7e00000)) >> 11;
            DWORD B1 = (((Colors >> 5) & 0xe000) | (Colors & 0x1f0000)) >> 13;
            Color[0] = B0 | G0 | R0;
            Color[1] = B1 | G1 | R1;
            Color[2] = (((G1 * 11 + G0 * 21) & 0x1fe000) | ((B1 * 11 + B0 * 21) & 0x1fe0) | ((R1 * 11 + R0 * 21) & 0x1fe00000)) >> 5;
            Color[3] = (((G1 * 21 + G0 * 11) & 0x1fe000) | ((B1 * 21 + B0 * 11) & 0x1fe0) | ((R1 * 21 + R0 * 11) & 0x1fe00000)) >> 5;

            DWORD AlphaBits = AlphaLo >> 16;
            DWORD *Row = Block;
            for (INT y = 0; y < BlockH; y++)
            {
                switch (y)
                {
                case 1: AlphaBits = (AlphaLo >> 28) | (AlphaHi << 4); break;
                case 2: AlphaBits = AlphaHi >> 8; break;
                }
                DWORD *Pixel = Row;
                for (INT x = 0; x < BlockW; x++, Pixel++)
                {
                    if (Pixel >= End)
                        return;
                    *Pixel = Alpha[AlphaBits & 7] | Color[Indices & 3];
                    Indices >>= 2;
                    AlphaBits >>= 3;
                }
                Row += Width;
            }
            Block += BlockW;
        }
        Block += Width * 3;
    }
}
