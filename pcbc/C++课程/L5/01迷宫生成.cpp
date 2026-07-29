#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int n;
    cin >> n;  // 输入矩阵维度
    
    srand(time(0));  // 设置随机种子
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (rand() % 2);  // 生成0或1
            if (j != n - 1) cout << " ";  // 最后一个数字后不加空格
        }
        cout << endl;  // 换行
    }
    
    return 0;
}
