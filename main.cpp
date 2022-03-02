#include <iostream>
#include <bitset>
#include <vector>
#include <random>
#include <unordered_map>

const int N = 875000;

std::unordered_map<char, short> dict = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
                           {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
                           {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14},
                           {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19},
                           {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24},
                           {'z', 25}};

void fill_vec (std::vector<std::string> &vec) {
    for (int i = 0; i < N; i++) {
        std::string s;
        for (int j = 0; j < 80; j++)
            s += char('a' + rand() % ('z' - 'a'));
        vec.push_back(s);
    }
}

struct node {
    std::vector<std::string> arr;
    struct node* nxt[26];
};

struct node* new_node()
{
    auto* tempNode = new node;
    for (int i = 0; i < 26; i++) {
        tempNode->nxt[i] = NULL;
    }
    return tempNode;
}

void msd_sort(struct node* root, int d, std::vector<std::string>& sorted_arr)
{
    if (d > 80) {
        return;
    }
    int j;
    //std::cout << root->arr.size() << "  ";
    //  Складываем в разные вёдра исходя из MSD
    for (int i = 0;
         i < root->arr.size();
         i++) {

        // Конвертируем нужный символ в число
        j = dict[(root->arr[i])[d]];

        // Добавляем новый индекс если его не существует
        if (root->nxt[j] == NULL) {
            root->nxt[j] = new_node();
        }

        // Помещаем элемент в j-й узел
        root->nxt[j]->arr.push_back(
                root->arr[i]);
    }

    // Снова сортируем каждого child с size > 1
    for (int i = 0; i < 26; i++) {

        // If root->next is NULL
        if (root->nxt[i] != NULL) {

            if (root->nxt[i]->arr.size()
                > 1) {

                // Рекурсивно сотрируем
                msd_sort(root->nxt[i],
                         d + 1,
                         sorted_arr);
            }

                // Если в узле один элемент,
                // значит он уже отсортирован
            else {
                sorted_arr.push_back(
                        root->nxt[i]->arr[0]);
            }
        }
    }
}

void print(std::vector<std::string> arr)
{
    for (int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << std::endl;

    std::cout << std::endl;
}




int main() {
    //cout<<char('a' + rand() % ('A' - 'a'))<<" ";

    struct node* root = new_node();
    {std::vector<std::string> vec;
    fill_vec(vec);
    root->arr = vec;}

    std::vector<std::string> sorted;

    auto start_time = clock();
    msd_sort(root, 0, sorted);
    std::cout << std::endl << clock() - start_time << "ms for " << N << std::endl;

    //print(sorted);

    return 0;
}
