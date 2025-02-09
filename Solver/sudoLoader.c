#include "sudoLoader.h"
#include "stdio.h"

//Convert a sudoku file in an array, then we can solve it
void Loader(char path[], int sudoku[81])
{

    /// - Open the text file
    FILE* txt = fopen(path,"r");

    size_t i = 0;
    char tmp[4];

    /// - Take three char
    while (fscanf(txt,"%s*", tmp)!=EOF)
    {
        for (size_t acc = 0;acc<3;acc++)
        {
            /// - For each char, 0 if it's a point, else the number
            if (tmp[acc] == '.')
                sudoku[i+acc] = 0;
            else
                sudoku[i+acc] = tmp[0+acc]-'0';
        }
        i+=3;
    }
    fclose(txt);
}


/// - Convert a sudoku array in a file
void Writer(int sudoku[81])
{
    /// - Open/create the file
    FILE* txt = fopen("sudo_resolved","w+");

    int i = 0;
    while(i<81)
    {
        if(i%9==0)
        {
            /// - End of the line
            fputc('\n', txt);
            if (i % 27 == 0)
                /// - End of the square vertical
                fputc('\n', txt);
        }
        else if (i%3==0)
            /// - End of the square horizontal
            fputc(' ',txt);
        if(sudoku[i]==0)
            /// - Dot if it's zero
            fputc('.',txt);
        else
            /// - To have the char value : ascii of 0 + number = char of the number
            fputc(48+sudoku[i],txt);
        i++;
    }
    fputc('\n',txt);
    fclose(txt);
}

