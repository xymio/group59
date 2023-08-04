#pragma once

#include <iostream>
#include<string>
using namespace std;

// ���ַ���ת��Ϊ4x4����
void StrToArray(unsigned char* plain, unsigned char parray[4][4])
{
    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // if (i<3)
            parray[j][i] = plain[k];
            //else
              //   parray[j][i] = 0;
            k++;
        }
    }

}

//��4x4����ת��Ϊ����
string ArrayToStr(unsigned char parray[4][4])
{
    string plain;
    //int k = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            plain += parray[j][i];
            //cout << plain<<endl;

        }
    }
    return plain;
}


// ��ӡ����
void ShowArray(unsigned char array[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%02X", array[i][j]);
            printf("\t");

        }
        printf("\n");
    }
    printf("\n");
}

//S��
const unsigned char S[16][16] =
{                      //4                     //8              //b         //d
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,  //1
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0, //2
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,//3
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,//4
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,//5
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,//6
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,//7
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,//8
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,//a
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,//c
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,//e
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

//�ֽڴ���
void SubBytes(unsigned char parray[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // ������
            int x = parray[i][j] / 16;
            // ������
            int y = parray[i][j] % 16;
            // S�д���
            parray[i][j] = S[x][y];
        }
    }

}

// ����λ
void ShiftRows(unsigned char parray[4][4])
{
    unsigned char temp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[i][j] = parray[i][j];


    // ��ʼ��λ
    for (int i = 0; i < 4; i++)
    {
        // ��һ�в���
        // �ڶ���������һ���ֽ�
        for (int j = 0; j < 4; j++)
            parray[i][j] = temp[i][(j + i) % 4];

    }

}


// �л��Ҫ�õľ���
const int c[4][4] =
{
    0x02,0x03,0x01,0x01,
    1,2,3,1,
    1,1,2,3,
    3,1,1,2
};

// ����{02}*{x}
unsigned char GFmu2(unsigned char x)
{

    // ����һλ
    unsigned char x_left = x << 1;

    // �ж�x���������λ�ǲ���Ϊ1
    unsigned char b7 = x & 0x80;

    // ���Ϊ1,���ƺ��ֵ��0001 1011 ���
    if (b7 != 0)
        x_left = x_left ^ 0x1b;
    return x_left;
}

// ����{03}*{x}
unsigned char GFmu3(unsigned char x)
{
    return GFmu2(x) ^ x;
}

// ���㵥��
unsigned char GFmu(int n, unsigned char x)
{
    unsigned char result = 0;
    if (n == 2)
        result = GFmu2(x);
    else if (n == 3)
        result = GFmu3(x);
    else if (n == 4)
        result = GFmu(2, GFmu2(x));
    else if (n == 8)
        result = GFmu(2, GFmu(4, x));
    else if (n == 9)
        result = x ^ GFmu(8, x);
    else if (n == 0x0e)
        result = GFmu(8, x) ^ (GFmu(4, x) ^ GFmu2(x));
    else if (n == 0x0d)
        result = GFmu(9, x) ^ GFmu(4, x);
    else if (n == 0x0b)
        result = GFmu(9, x) ^ GFmu2(x);
    else
        result = x;
    return result;

}

// �л��
void MixColums(unsigned char parray[4][4])
{
    // ����parray
    unsigned char temp[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            temp[i][j] = parray[i][j];
    }

    //��ʼ����
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            parray[i][j] = GFmu(c[i][0], temp[0][j]) ^ GFmu(c[i][1], temp[1][j]) ^ GFmu(c[i][2], temp[2][j]) ^ GFmu(c[i][3], temp[3][j]);
        }
    }
}


// ��һ��4�ֽ����ֿ�������
void SplitNumToArray(int num, unsigned char numarray[4])
{
    numarray[0] = num >> 24;
    numarray[1] = num >> 16;
    numarray[2] = num >> 8;
    numarray[3] = num;

}

// ������ϳ�һ��4�ֽ���
int CombineArrayToNum(unsigned char numarray[4])
{
    int num = 0;
    num = numarray[0];
    num = num << 8;
    num += numarray[1];
    num = num << 8;
    num += numarray[2];
    num = num << 8;
    num += numarray[3];

    return num;
}

// ����Կ��ÿһ�кϳ�һ��4�ֽ���
void KeyColumsCombine(unsigned char karray[4][4], int carray[44])
{
    for (int i = 0; i < 4; i++)
    {
        // temp��4����ž����ÿһ��
        unsigned char temp[4];
        temp[0] = karray[0][i];
        temp[1] = karray[1][i];
        temp[2] = karray[2][i];
        temp[3] = karray[3][i];

        // �������ÿһ�кϳ�һ������������չ��Կ����
        carray[i] = CombineArrayToNum(temp);

    }
}




// ������ֵ��
static const int Rcon[10] =
{ 0x01000000, 0x02000000,
    0x04000000, 0x08000000,
    0x10000000, 0x20000000,
    0x40000000, 0x80000000,
    0x1b000000, 0x36000000 };



// g����
int g(int carray, int round)
{
    unsigned char numarray[4];

    // ��4�ֽ����ֿ�
    SplitNumToArray(carray, numarray);

    // ѭ������һλ
    unsigned char temp = numarray[0];
    for (int j = 0; j < 3; j++)
        numarray[j] = numarray[(j + 1) % 4];
    numarray[3] = temp;


    // ��s�����ֽڴ���
    for (int j = 0; j < 4; j++)
    {
        // ������
        int x = numarray[j] / 16;
        // ������
        int y = numarray[j] % 16;

        numarray[j] = S[x][y];

    }
    /*
    cout << "\n" << "�ֽڴ�����";
    for (int j = 0; j < 4; j++)
    {
        printf("%02x%s", numarray[j], "\t");
    }
    */

    // ���ϳ�һ��4�ֽ���
    int num = 0;
    num = CombineArrayToNum(numarray);

    // ��Rcon���
    num = num ^ Rcon[round];

    return num;
}

// ��չ��Կ
int carray[44];

// ��չ��Կ karrayΪ����Կ
void KeyExtend(unsigned char karray[4][4])
{
    // ������Կ������չ����
    KeyColumsCombine(karray, carray);

    for (int i = 4, j = 0; i < 44; i++)
    {
        // 4��������Ҫ����g����
        if (i % 4 == 0)
        {
            carray[i] = carray[i - 4] ^ g(carray[i - 1], j);

            j++; // ��һ��
        }
        else
            carray[i] = carray[i - 1] ^ carray[i - 4];
        //cout << carray[i];
    }
}

// ��������Կ,������
void AddKeyRound(unsigned char parray[4][4], int round)
{
    //cout <<"\n"<< round << "����Կ:";

    // ����е�����Կ
    unsigned char rarray[4];

    for (int i = 0; i < 4; i++)
    {
        // ��carray[44]��ȡ��������rarray[4]
        SplitNumToArray(carray[round * 4 + i], rarray);

        // һ��һ�м���
        for (int j = 0; j < 4; j++)
        {
            //printf("%02x%s",rarray[j],"\t"); 
            //printf("%02x%s", parray[j][i], "\t");
            parray[j][i] = parray[j][i] ^ rarray[j];
            // printf("%02x%s", parray[j][i], "\t");
        }

    }

}


//��S��
const unsigned char ReS[16][16] =
{
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

// ���б任
void InvSubBytes(unsigned char parray[4][4])
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // ������
            int x = parray[i][j] / 16;
            // ������
            int y = parray[i][j] % 16;
            // S�д���
            parray[i][j] = ReS[x][y];
        }
    }

}


void InvShiftRows(unsigned char parray[4][4])
{
    unsigned char temp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[i][j] = parray[i][j];

    // ��ʼ��λ

        // ��һ�в���

        // �������ֽ�
    for (int j = 0; j < 4; j++)
    {
        parray[1][j] = temp[1][(j + 3) % 4];
        parray[2][j] = temp[2][(j + 2) % 4];
        parray[3][j] = temp[3][(j + 1) % 4];
    }


}
const int Rec[4][4] =
{
    0x0e,0x0b,0x0d,0x09,
    0x09,0x0e,0x0b,0x0d,
    0x0d,0x09,0x0e,0x0b,
    0x0b,0x0d,0x09,0x0e
};

void InvMixColumns(unsigned char parray[4][4])
{
    // ����parray
    unsigned char temp[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            temp[i][j] = parray[i][j];
    }

    //��ʼ����
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            parray[i][j] = GFmu(Rec[i][0], temp[0][j]) ^ GFmu(Rec[i][1], temp[1][j]) ^ GFmu(Rec[i][2], temp[2][j]) ^ GFmu(Rec[i][3], temp[3][j]);
        }
    }
}
string AES_enc_128(unsigned char* input, unsigned char* key)
{


    // ����
    //unsigned char input[16] = "202100460145";

     //����Կ
    //unsigned char key[16] = "202100460145";

    // ��Կ�������������
    unsigned char karray[4][4];
    unsigned char parray[4][4];

    // ����Կת��Ϊ����
    StrToArray(key, karray);
    //cout << "��Կ���飺" << "\n";
    //ShowArray(karray);

    //������ת��Ϊ����
    StrToArray(input, parray);
    //cout << "�������飺" << "\n";
     //ShowArray(parray);

     // ��չ��Կ
    KeyExtend(karray);

    // ��һ�ּ���
    AddKeyRound(parray, 0);
    //cout << "��һ�ּ��ܺ�"<<"\n";
    //ShowArray(parray);


    // ǰ����
    for (int i = 1; i < 11; i++)
    {
        //  �ֽڴ���
        SubBytes(parray);
        //cout << "�ֽڴ�����"<<"\n";
         //ShowArray(parray);

         // ����λ
        ShiftRows(parray);
        //cout << "����λ��" << "\n";
        //ShowArray(parray);

        // �л��
        if (i < 10)
        {
            MixColums(parray);
            //cout << "�л�Ϻ�" << "\n";
           // ShowArray(parray);
        }

        // ����
        AddKeyRound(parray, i);
        //cout << "һ�ּ��ܺ�" << "\n";
       // ShowArray(parray);
    }

    // ShowArray(parray);

     //ת��Ϊ�ַ���
    string m;
    m = ArrayToStr(parray);
    return m;

}
string AES_dec_128(unsigned char* input, unsigned char* key)
{

    // ��Կ�������������
    unsigned char karray[4][4];
    unsigned char parray[4][4];

    // ����Կת��Ϊ����
    StrToArray(key, karray);
    //cout << "��Կ���飺" << "\n";
    //ShowArray(karray);

    //������ת��Ϊ����
    StrToArray(input, parray);
    //cout << "�������飺" << "\n";
    //ShowArray(parray);

     // ��չ��Կ
    KeyExtend(karray);

    // ��һ�ֽ���
    AddKeyRound(parray, 10);
    //cout << "��һ�ֽ��ܺ�"<<"\n";
    //ShowArray(parray);


    // ǰ����
    for (int i = 9; i >= 0; i--)
    {


        // ������λ
        InvShiftRows(parray);
        //cout << "������λ��" << "\n";
        //ShowArray(parray);

        // ���ֽڴ���
        InvSubBytes(parray);
        //cout << "���ֽڴ�����"<<"\n";
       //ShowArray(parray);

       // ����
        AddKeyRound(parray, i);
        // cout << "һ�ֽ��ܺ�" << "\n";
        // ShowArray(parray);

         // ���л��
        if (i > 0)
        {
            InvMixColumns(parray);
            // cout << "���л�Ϻ�" << "\n";
            // ShowArray(parray);
        }

    }

    // ShowArray(parray);

     //ת��Ϊ�ַ���
    string m;
    m = ArrayToStr(parray);
    return m;
}


string AES_enc(string plain, string key_s)
{
    string m;
    int i;
    int len = plain.length();


    unsigned char key[16];
    for (int j = 0; j < 16; j++)
        key[j] = key_s[j];

    for (i = 0; i < len; i += 16)
    {
        unsigned char input[16];

        if (len - i < 16)
        {
            for (int j = 0; j < len - i; j++)
                input[j] = plain[i + j];
            for (int j = len - i; j < 16; j++)
                input[j] = 0;
        }
        else
        {
            for (int j = 0; j < 16; j++)
                input[j] = plain[i + j];
        }
        m += AES_enc_128(input, key);

    }

    return m;
}

string AES_dec(string m, string key_s)
{
    string plain;
    int i;
    int len = m.length();

    unsigned char key[16];
    for (int j = 0; j < 16; j++)
        key[j] = key_s[j];

    for (i = 0; i < len; i += 16)
    {
        unsigned char input[16];

        if (len - i < 16)
        {
            for (int j = i; j < len - i; j++)
                input[j] = m[j];
            for (int j = len - i; j < 16; j++)
                input[j] = 0;
        }
        else
        {
            for (int j = 0; j < 16; j++)
                input[j] = m[i + j];
        }
        plain += AES_dec_128(input, key);

    }
    return plain;
}
/*
int main()
{
   string plain = "202100460145";
   string key_s = "202100460145000";
   string m;

    m=AES_enc(plain,key_s);
    plain=AES_dec(m ,key_s);
    cout <<endl<< plain << endl;
    return 0;
}


*/