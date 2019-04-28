#include <bits/stdc++.h>
using namespace std;

#define mx 100

int main ()
{
    //freopen("in.txt", "r", stdin);
    int k;
    cout << "Enter the No of Data Bits you want to Enter (Maximum 20) : ";
    cin >> k;

    int row = k, col = 1;
    int dataWord[mx][mx];

    cout << "Enter the Data Bits One by One:\n";

    for(int i=1; i<=row; i++)
        for(int j=1; j<=col; j++)
            cin >> dataWord[i][j];

    cout << "\nData bits entered(block wise):\n";

    for(int i=1; i<=row; i++){
        for(int j=1; j<=col; j++){
            cout << dataWord[i][j] << " ";
        }
        cout << endl;
    }

    int r = 0;
    while(col+1+r > pow(2, r)) r++;

    int codeWord[mx][mx];
    int parityBit = 0;
    int y = 0;
    col += r;

    for(int i=1; i<=row; i++){
        parityBit = 0;
        y = 1;
        for(int j=1; j<=col; j++){
            if (j == pow(2, parityBit)){
                codeWord[i][j] = 0;
                parityBit++;
            }
            else
                codeWord[i][j] = dataWord[i][y++];
        }
    }

    cout << "\nData Bits are Encoded with Parity bits(0):\n";

    for(int i=1; i<=row; i++){
        for(int j=1; j<=col; j++)
            cout << codeWord[i][j] << " ";

        cout << endl;
    }

    for(int i=1; i<=row; i++){
        parityBit = 0;
        for(int j=1; j<=col; j=pow(2, parityBit)){
            parityBit++;
            int parity = 0;
            int t = j, cnt = 0;

            while(t <= col){
                parity = parity ^ codeWord[i][t];
                t++;
                cnt++;
                if(cnt == j){
                    t = t+j;
                    cnt = 0;
                }
            }
            codeWord[i][j] = parity;
        }
    }

    cout << "\nHamming codeword bits for even parity are(block wise):\n";

    for (int i=1; i<=row; i++){
        for(int j=1; j<=col; j++)
            cout << codeWord[i][j] << " ";

        cout << endl;
    }

    cout << endl;

    cout << "Do you want to send this Data (Y/N): ";
    char c; cin >> c;
    if(c == 'y' or c == 'Y'){
        cout << endl << "Transmitted Data:\n";

        for(int j=1; j<=col; j++){
            for(int i=1; i<=row; i++)
                cout << codeWord[i][j] << ' ';
        }

        cout << "\n\nEnter received codeword one by one (According to transmitted data):\n";

        int receivedData[mx][mx];
        for(int j=1; j<=col; j++){
            for(int i=1; i<=row; i++)
                cin >> receivedData[i][j];
        }

        cout << endl << "Received code word:\n";

        for(int i=1; i<=row; i++){
            for(int j=1; j<=col; j++)
                cout << receivedData[i][j] << " ";

            cout << endl;
        }
        cout << endl;

        vector <int> parityData[mx];
        bool error = false;

        cout << "Position to be XOR:\n\n";
        for(int i=1; i<=row; i++){
            parityBit = 0;
            for(int j=1; j<=col; j=pow(2, parityBit)){
                parityBit++;
                int parity = 0;

                int t = j, cnt = 0;

                cout << "Position " << i << "," << j << ": ";
                while(t <= col){
                    cout << t << ' ';
                    parity = parity ^ receivedData[i][t];
                    t++;
                    cnt++;
                    if(cnt == j){
                        t = t+j;
                        cnt = 0;
                    }
                }
                cout << endl;

                parityData[i].push_back(parity);

                if(parity ^ receivedData[i][j] != receivedData[i][j])
                    error = true;
            }
            cout << endl;
        }

        if(error){
            cout << "Data bits are corrupted!!!" << endl << endl;
            cout << "Correct Data bits are:\n";

            for(int i=1; i<=row; i++){
                int pos = 0;
                for(int j=0; j<=parityData[i].size(); j++){
                    if(parityData[i][j] == 1)
                        pos = pos + pow(2, j);
                }
                receivedData[i][pos] = receivedData[i][pos] ^ 1;
            }

            cout << endl;
            for(int i=1; i<=row; i++){
                for(int j=1; j<=col; j++)
                    cout << receivedData[i][j] << " ";

                cout << endl;
            }
        }
        else
            cout << "Data are fine" << endl;

        cout << endl << endl;
    }

    return 0;
}
