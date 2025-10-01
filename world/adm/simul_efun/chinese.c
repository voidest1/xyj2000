// cracked by vikee 2/09/2002   vikee@263.net

string to_chinese(string str)
{
	return CHINESE_D->chinese(str);
}

string chinese_number(int i)
{
	return CHINESE_D->chinese_number(i);
}

int is_chinese(string s) {
    int i, n, b;
    if (!stringp(s)) return 0;
    n = strlen(s);
    if (n == 0) return 0;

    for (i = 0; i < n; i++) {
        b = s[i];
        if (b < 0) b += 256;        // 避免有符号字节
        if (b < 0x80) return 0;     // 发现 ASCII，直接判 0
    }
    return 1;                       // 全部非 ASCII
}