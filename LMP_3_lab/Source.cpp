#include<iostream>
#include<fstream>
#include<string>
#include<vector>
//Задана система двусторонних дорог. Определить, можно ли, закрыв какие-либо три из них,
//добиться того, чтобы из города А нельзя было попасть в город Б

using std::cout;

struct Roads {
    int n;
    bool** map;
    bool** used;
    std::vector<int> v;

    Roads(std::ifstream& file)
    {
        file >> n;
        used = new bool* [n];
        map = new bool* [n];
        for (int i = 0; i < n; i++)
        {
            used[i] = new bool[n];
            map[i] = new bool[n];
            for (int j = 0; j < n; j++)
            {
                file >> map[i][j];
                used[i][j] = 0;
            }
        }
        real_roads(v);
    }

    void print() 
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << map[i][j] << ' ';
            }
            cout << '\n';
        }
        
    }

    ~Roads()
    {
        for (int i=0; i < n; i++)
        {
            delete[]map[i];
            delete[] used[i];
        }
        delete map;
        delete used;
    }

    bool find_roads(int ind)
    {
        bool result = 0;
        if (ind == 1)
            result = 1;
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (map[ind][i] == 1 && used[ind][i] != 1)
                {
                    used[ind][i] = 1;
                    used[i][ind] = 1;
                    result+=find_roads(i);
                    used[ind][i] = 0;
                    used[i][ind] = 0;
                }
            }
        }
        return result;
    }

    void real_roads(std::vector<int>&v)
    {
        for (int i = 0; i < n-1; i++)
        {
            for (int j = i+1; j < n; j++)
            {
                if(map[i][j]==1)
                    v.push_back(n * i + j);
            }
        }
    }

    bool gen(int num, int last, std::vector<int>& a)
    {
        bool result = false;
        if (num == 3)
        {
            for (int i = 0; i < 3; i++)
            {
                map[a[i] / n][a[i] % n] = 0;
                map[a[i] % n][a[i] / n] = 0;
            }
            result += find_roads(0);
            for (int i = 0; i < 3; i++)
            {
                map[a[i] / n][a[i] % n] = 1;
                map[a[i] % n][a[i] / n] = 1;
            }
        }
        else
        {
            for (int i = last+1 ; i < v.size(); i++) {
                a.push_back(v[i]);
                result+=gen(num + 1, i, a);
                a.pop_back();
            }
        }
        return result;
    }
    void task()
    {
        bool result = 0;
        std::vector<int> v;
        real_roads(v);
        if (v.size() < 3)
            cout << "There're less than 3 roads in the graph\n";
        else
        {
            std::vector<int> a;
            if (gen(0, -1, a))
                cout << "You can get from city A to B\n";
            else
                cout << "You CAN'T get from city A to B\n";
        }
    }

    void print_v()
    {
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << ' ';
        }
        cout << '\n';
    }

};

int main() 
{
    std::ifstream file("data1.txt");
    if (file)
    {
        Roads obj(file);
        //int start = 1, end = 2;
        obj.print();
        obj.task();
        file.close();
    }
    else
        cout << "File isn't open\n";

    return 0;
}