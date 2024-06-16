//文字コードを指定するC言語

    unsigned char *str = "〒123-4567 maison○□12号室";
    unsigned char buf[256];
    unsigned char *sp = str, *bp = buf;
    unsigned char c1 = 0, c2 = 0;
    while (*sp != '\0'){
        printf("%x ", *sp);
        if ((*sp & 0xf0) == 0xe0){ // 上位4ビットが1110なら、3バイト文字の1バイト目
            *bp = '|';
            bp++;
            c1 = *sp;
        }
        else if ((*sp & 0xc0) == 0x80){ // 上位2ビットが10なら、他バイト文字の2バイト目以降
            if (c2 == 0){
                c2 = *sp;
            }
            else {
                *bp = c1;
                bp++;
                *bp = c2;
                bp++;
                *bp = *sp;
                bp++;
                c1 = c2 = 0;
            }
        }
        else if ((*sp & 0x80) == 0){ // 1バイト文字の場合
            *bp = '|';
            bp++;
            *bp = *sp;
            bp++;
        }
        sp++;
    }
    *bp = '\0';
    printf("\n%s\n", buf);
    return 0;
