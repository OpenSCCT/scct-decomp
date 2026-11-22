/* FAKEMATCH: the original members in this range are not recovered; these padding members are not
   named by offset and only push later members into place. */
struct VersusScriptFrame {
    unsigned char unknown[12];
    const unsigned char *code;
};
