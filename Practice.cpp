#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <numeric>
#include <vector>
#include <ranges>
#include <stack>
#include <sstream>
#include <climits>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <map>
#include <unordered_map>
#include <cctype>
#include <queue>
#include <optional>


using namespace std;
using namespace std::literals;
namespace tools {
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };

    class ListConverter {
    public:
        ListNode* createList(const std::vector<int>& vec) {
            if (vec.empty()) return nullptr;
            ListNode* head = new ListNode(vec[0]);
            ListNode* curr = head;
            for (size_t i = 1; i < vec.size(); ++i) {
                curr->next = new ListNode(vec[i]);
                curr = curr->next;
            }
            return head;
        }

        std::vector<int> listToVector(ListNode* head) {
            std::vector<int> res;
            while (head != nullptr) {
                res.push_back(head->val);
                head = head->next;
            }
            return res;
        }
    };

    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };

    template <typename T>
    void PrintVector(const std::vector<T>& vec) {
        std::cout << "{ ";
        for (const auto& elem : vec) {
            std::cout << elem << ' ';
        }
        std::cout << "}\n";
    }
}

namespace problems {
    //слиять слова по буквам по очереди
    class MergeAlternately {
    public:
        string mergeAlternately(const string& word1, const  string& word2) {
            string output{}; //выходное значение строки
            size_t i{}; //счётчик/индекс
            //пока размер выходного слова меньше суммы входных
            while (output.size() < word1.size() + word2.size()) {
                if (i < word1.size()) { //индекс меньше размера?
                    output.push_back(word1[i]); //тогда добавляю в выходное слово букву
                }
                if (i < word2.size()) {
                    output.push_back(word2[i]);
                }
                ++i;    //увеличиваю индекс
            }
            return output;
        }
    };

    //Алгоритм Евклида
    class GCDOfStrings {
    private:
        size_t FindNOD(size_t first, size_t second){
            size_t i = std::min(first, second);
            for (; i != 0; --i) {
                if (first % i == 0 && second % i == 0) {
                    break;
                }
            }
            return i;
        }
    public:
        string gcdOfStrings(const string& str1, const string& str2) {
            // Базовое условие: если общий делитель существует, 
            // то конкатенация str1 + str2 должна быть в точности равна str2 + str1. 
            // Если они не равны, общего делителя нет 
            if (str1 + str2 != str2 + str1) {
                return {};
            }

            //моё решение (3мс)
            size_t block_lenght = FindNOD(str1.size(), str2.size());
            return str1.substr(0, block_lenght);

            ////Эталонное решение (0мс)
            //return str1.substr(0, std::gcd(str1.size(), str2.size()));
        }
    };

    //больше ли конфет если дать еще конфет
    class KidsWithCandies {
    public:
        vector<bool> kidsWithCandies(const vector<int>& candies, int extraCandies) {
            vector<bool> answers(candies.size(), false);
            auto answers_it = answers.begin();
            int max_element = *ranges::max_element(candies);
            for (const auto candy : candies) {
                *answers_it =  candy + extraCandies >= max_element ?  true : false;
                answers_it++;
            }

            return answers;
        }
    };

    //диллема писсуаров
    class CanPlaceFlowers {
    public:
        bool canPlaceFlowers(const vector<int>& flowerbed, int n) {
            vector<int> copy = flowerbed;
            for (int i = 0; i < copy.size(); ++i) {
                if (i == 0) { //если это первый элемент
                    //то надо проверить ноль ли он и следующий элемент
                    if (copy[0] == 0 && copy[std::min(i + 1, static_cast<int>(copy.size()) - 1)] == 0) {
                        //если да, то забираем в него единицу из n
                        copy[0] = 1;
                        --n;
                        ++i; //пропускаем следующий элемент, у него слева посажен цветок
                    }
                } //если это последний элемент
                else if (i == copy.size() - 1) {
                    //то надо проверить ноль ли он и предыдущий элемент
                    if (copy[i] == 0 && copy[std::max(i - 1, 0)] == 0) {
                        copy[i] = 1;
                        --n;
                    }
                }//во всех остальных случаях
                else {
                    if (copy[i] == 0 && copy[i - 1] == 0 && copy[i + 1] == 0) {
                        copy[i] = 1;
                        --n;
                        ++i; //пропускаем следующий элемент, у него слева посажен цветок
                    }
                }
            }
            return n <= 0;
        }
    };

    //поменять местами гласные в словах в обратную сторону 
    class ReverseVowels {
    public:
        string reverseVowels(string s) {
            std::string vowels{ "aeiouAEIOU" };
            std::stack<char> chars_stack;

            //записываем все гласные в мапу
            for (int i = 0; i < s.size(); ++i) {
                auto vowel_iter = std::ranges::find(vowels, s[i]);
                if (vowel_iter != vowels.end()) {
                    chars_stack.push(s[i]);
                }
            }
            //так же проходим по строке s, но теперь заменяем буквы
            for (auto& ch : s) {
                if (std::ranges::find(vowels, ch) != vowels.end()) {
                    ch = chars_stack.top();
                    chars_stack.pop();
                }
            }
            return s;
        }
    };

    //поменять местами слова в предложении в обратную сторону 
    class ReverseWords {
    public:
        string reverseWords(string s) {
            std::istringstream is{ s };
            std::string word{};
            std::string reversed_s;
            std::vector<std::string> str_vec{};

            while (is >> word) {
                str_vec.push_back(word);
            }

            str_vec = { str_vec.rbegin(), str_vec.rend() };
            bool is_first = true;
            for (auto& word : str_vec) {
                if (!is_first) {
                    reversed_s += " ";
                }
                reversed_s += word;
                is_first = false;
            }
            
            return reversed_s;
        }
    };

    //умножение на все элементы кроме себя
    class ProductExceptSelf {
    public:
        vector<int> productExceptSelf(const vector<int>& nums) {
            size_t  size = nums.size();
            std::vector<int> output(size, 1);
            int prefix{ 1 }; 
            //при проходу вверх записываем значение префикса
            //затем умножаем префикс на текущее nums[i]
            for (int i = 0; i < size; ++i) {
                output[i] = prefix;
                prefix *= nums[i];
            }
            int postfix{1};
            //В обратную сторону уже не записываем, а перезаписываем через умножение
            for (int i = size - 1; i >= 0; --i) {
                output[i] *= postfix;
                postfix *= nums[i];
            }
            return output;
        }
    };

    //поиск восходящей тройки значений
    class IncreasingTriplet {
    public:
        bool increasingTriplet(const vector<int>& nums) {
            int min1{ INT32_MAX };
            int min2{ INT32_MAX };
            for (const auto& num : nums) {
                if (num <= min1) {
                    min1 = num;
                }
                else if (num <= min2) {
                    min2 = num;
                }
                else {
                    return true;
                }
            }

            return false;
        }
    };

    //сжатие строки
    class Сompressor {
    public:
        int compress(vector<char>& chars) {
            int size = chars.size();
            //если в массиве только один символ - ну там только 1 символ.
            if (size == 1) { return 1; }
            int index{ 0 };
            int cur_len{ 1 };

            //идём до size включительно чтобы обработать последний символ
            for (int i = 1; i <= size; ++i) {
                // Если дошли до конца или символ изменился
                if (i == size || chars[i] != chars[i - 1]) {
                    chars[index++] = chars[i - 1];

                    //если счетчик больше 1 то записываем его цифры
                    if (cur_len > 1) {
                        std::string count{ to_string(cur_len) };
                        for (auto& n : count) {
                            chars[index++] = n;
                        }
                    }
                    //сбрасываем счетчик
                    cur_len = 1;
                }else {
                    ++cur_len;
                }
            }
            return index;
        }
    };

    //снежный ком
    class MoveZeroes {
    public:
        void moveZeroes(vector<int>& nums) {
            //мое решение
            std::vector<int> output(nums.size(), 0);
            int iter = 0;
            for (const auto& n : nums) {
                if (n != 0) {
                    output[iter] = n;
                    ++iter;
                }
            }
            std::swap(output, nums);

            ////эталонное решение
            //int count_of_zeros{ };
            //for (int i = 0; i < nums.size(); ++i) {
            //    //если этот элемент == 0 то прибавляю счетчик
            //    if (nums[i] == 0) {
            //        ++count_of_zeros;
            //    }
            ////если не ноль и были ноли, то меняю текущий элемент с первым нолем в снежном коме
            //    else if (count_of_zeros > 0) {
            //        std::swap(nums[i], nums[i - count_of_zeros]);
            //    }
            //}
        }
    };

    //является ли строка подпоследовательностью другой строки
    class IsSubsequence {
    public:
        bool isSubsequence(const string& s, const string& t) {
            //если подстрока пуста лил они оба пусты, возвращается true
            //типа пустота вхожа в строку любой длины, даже нулевой.
            if (s.size() == 0 || (s.size() == 0 && t.size() == 0)) { return true; }
            //если подстрока больше строки то это уже не подстрока
            if (s.size() > t.size() || t.size() == 0) { return false; }
            ////для каждого символа в подстроке задаю индекс
            //std::vector<char> psevdo_map_of_s(s.begin(), s.end());
            //если запоминать позицию предыдущего элемента
            int position{INT32_MAX};
            //прохожу s с конца, нахожу позицию элемента в t, записываю позицию в psevdo_map_of_s
            for (int i = s.size() - 1; i >= 0; --i) {
                auto it = std::find(t.rbegin(), t.rend(), s[i]);
                //если элемент не найден - это не подстрока
                if (it == t.rend()) { return false; }

                while (it != t.rend()) {
                    size_t distance = std::ranges::distance(it, t.rend());
                    //если дистанция меньше, то записываю и заканчиваю цикл
                    if (distance < position) {
                        position = distance;
                        break;
                    }
                    //если нет, то ищу следующий элемент
                    it = std::find(++it, t.rend(), s[i]);
                }
                //если вышло из цикла изза конца массива, то возвращаю false
                //но только если position != 0
                if (it == t.rend() && position !=0) { return false; }
            }
            //в остальных случаях все ок
            return true;

            ////Эталонное решение
            //int s_iter{};
            //int t_iter{};
            //while(s_iter < s.size() && t_iter < t.size()) {
            //    if (s[s_iter] == t[t_iter]) {
            //        ++s_iter;
            //    }
            //    ++t_iter;
            //}
            //return s_iter == s.size();
        }
    };

    //Метод двух указателей
    class MaxArea {
    public:
        int maxArea(vector<int>& height) {
            //беру два итератора ( указателя) на начало и конец
            auto first_elem_it = height.begin();
            auto last_elem_it = height.end() - 1;
            int tank{};     //для записи максимального значения объема воды
            int water{};    //для записи расчетного значения объема воды
            int distance{}; //для записи расчетного расстояния между элементами
            for (int i = 0; i < height.size(); ++i) {
                //получаю дистанцию (ширину прямоугольника)
                distance = std::ranges::distance(first_elem_it, last_elem_it);
                //получаю площадь по наименьшей стороне (вода не может быть выше такой стенки)
                water = std::min(*first_elem_it, *last_elem_it) * distance;
                //если рассчетное значение получилось выше - записываем его
                tank = water > tank ? water : tank;
                //если это были соседние элементы - заканчиваем подсчеты
                if (distance <= 1) { break; }
                //если нет - пробуем следующую стенку от низшей из текущих
                *first_elem_it < *last_elem_it ? ++first_elem_it : --last_elem_it;
            }
            return tank;
        }
    };

    //Количество пар с суммой K
    class MaxOperations {
    public:
        int maxOperations(vector<int>& nums, int k) {
            //сортируем массив
            std::ranges::sort(nums);
            //берем 2 крайних индекса 
            size_t index_l{ 0 };
            size_t index_r{ nums.size() - 1 };
            int count{};
            //пока левый индекс меньше правого проверяем на сумму.
            while (index_l < index_r) {
                //если сумма меньше к, то продвигаем дальше левый индекс
                if (nums[index_l] + nums[index_r] < k) {
                    ++index_l;
                }   //если больше - продвигаем правый 
                else if (nums[index_l] + nums[index_r] > k) {
                    --index_r;
                }   //если сумма равна к, то мы нашли пару, увеличиваем счетчик и продвигаем оба итератора дальше
                else { 
                    ++count;
                    ++index_l;
                    --index_r;
                }
            }

            return count;
        }
    };

    //Максимальная последовательность
    class FindMaxAverage {
    public:
        double findMaxAverage(vector<int>& nums, int k) {
            if (nums.size() == 1) {
                return static_cast<double>(nums[0]);
            }
            //double answer{std::numeric_limits<double>::lowest()};
            double answer{};
            int summ{};
            //сначала беру и сохраняю сумму от нулевого индекса до индекса i = k-1. 
            //затем прохожу по массиву пока i < size(), прибавляю к сумме значение текущего индекса и вычитаю значение i-k;
            //после этого делю на k и сравниваю полученное значение с answer. Если полученное больше - записываю.

            //получаю сумму первых чисел
            for (int i = 0; i < k; ++i) {
                summ += nums[i];
            }
            //записываю первое значение answer
            answer = static_cast<double>(summ) / k;

            //теперь прохожу по массиву
            for (int i = k; i < nums.size(); ++i) {
                summ -= nums[i - k]; //удаляю левое значение массива
                summ += nums[i]; //прибавляю текущее
                double pretendent = static_cast<double>(summ) / k;
                if (pretendent > answer) {
                    answer = pretendent;
                }
            }
            return answer;
        }
    };

    //Максимальное кол-во гласных в окне
    class MaxVowels {
    public:
        int maxVowels(string s, int k) {
            const std::string vovels{ "aeiou" };
            int count{};
            int max_count{};
            int i = 0;
            //записываю кол-во гласных в первом окне
            for (; i < k; ++i) {
                if (std::ranges::find(vovels, s[i]) != vovels.end()) {
                    ++count;
                }
            }
            //записываю кол-во гласных как первый найденный максимум
            max_count = count;
            //проходя дальше по тексту
            for (i = k; i < s.size(); ++i) {
                //если текущий символ - гласная - прибавляю к счетчику единицу
                if (std::ranges::find(vovels, s[i]) != vovels.end()) {
                    ++count;
                }
                //если символ ушедший из окна - гласная, то уменьшаю счетчик
                if (std::ranges::find(vovels, s[i - k]) != vovels.end()) {
                    --count;
                }
                //если значение счетчика выше сохраненного максимума - перезаписываю максимум
                if (count > max_count) {
                    max_count = count;
                }
            }
            return max_count;
        }
    };

    //максимальная длина единиц, если некоторые нули можно поменять на единицы
    class LongestOnes {
    public:
        int longestOnes(vector<int>& nums, int k) {
            int left_index{ 0 };
            int right_index{ 0 };
            int count{0};
            int max_size{0};
            for (; right_index < nums.size(); ++right_index) {
                //если правый элемент = 0, прибавляю счетчик
                if (nums[right_index] == 0) {
                    ++count;
                    //если счетчик переполнился - двигаю левую границу пока счетчик не будет <=k
                    while (count > k) {
                        if (nums[left_index] == 0) {
                            --count;
                        }
                        ++left_index;
                    }
                }
                //каждый шаг записываю новый рекорд, если он есть
                max_size = std::max(max_size, right_index - left_index + 1);
            }
            return max_size;
        }
    };

    //точно то же самое что и предыдущий, но k всегда = 1
    class LongestSubarray {
    public:
        int longestSubarray(vector<int>& nums) {
            int left_index{ 0 };
            int right_index{ 0 };
            int count{ 0 };
            int max_size{ 0 };
            int k = 1;
            for (; right_index < nums.size(); ++right_index) {
                //если правый элемент = 0, прибавляю счетчик
                if (nums[right_index] == 0) {
                    ++count;
                    //если счетчик переполнился - двигаю левую границу пока счетчик не будет <=k
                    while (count > k) {
                        if (nums[left_index] == 0) {
                            --count;
                        }
                        ++left_index;
                    }
                }
                //каждый шаг записываю новый рекорд, если он есть
                max_size = std::max(max_size, right_index - left_index + 1);
            }
            return max_size -1;
        }
    };

    class LargestAltitude {
    public:
        int largestAltitude(const vector<int>& gain) {
            int max_altitude{ 0 };
            int cur_height{ 0 };
            for (const int h : gain) {
                cur_height += h;
                max_altitude = std::max(max_altitude, cur_height);
            }
            return max_altitude;
        }
    };

    class PivotIndex {
    public:
        int pivotIndex(const vector<int>& nums) {
            int r_summ{ 0 };
            int l_summ{ 0 };
            //считаю вообще все элементы, они пока все справа
            for (int num : nums) {
                r_summ += num;
            }
            for (int i = 0; i < nums.size(); ++i) {
                //мы на i-том элементе. Он не считается. Только слева и справа от него
                //поэтому удаляем из суммы правых элементов, но пока не добавляем в левые
                r_summ -= nums[i];
                //если суммы сравнялись - индекс найден
                if (l_summ == r_summ) {
                    return i;
                }
                //если нет - добавляем число по индексу в левую сумму и идем дальше
                l_summ += nums[i];
            }
            //если цикл не вернул значение значит требуемого индекса не было
            return -1;
        }
    };

    class FindDifference {
    public:
        vector<vector<int>> findDifference(const vector<int>& nums1, const vector<int>& nums2) {
            //Надо сначала создать множество уникальных элементов
            std::unordered_set<int> set1{ nums1.begin(), nums1.end() };
            std::unordered_set<int> set2{ nums2.begin(), nums2.end() };

            //если нашел в сет число, которое есть в противоположном массиве - удалаю из сета
            //с константными ссылками на инты прога работает в 2-3 раза быстрее
            for (const int& n : nums1) {
                if (set2.contains(n)) {
                    set2.erase(n);
                }
            }
            for (const int& n : nums2) {
                if (set1.contains(n)) {
                    set1.erase(n);
                }
            }
            return { {set1.begin(), set1.end()}, {set2.begin(), set2.end()} };
        }
    };

    //Оригинальные ли количества вхождений элементов в массиве?
    class UniqueOccurrences {
    public:
        bool uniqueOccurrences(vector<int>& arr) {
            ////моё решение:
            ////создаю мапу для подсчета
            //std::map<int, int> exclusive{};
            ////подсчитываю все вхождения элементов
            //for (const int& n : arr) {
            //    exclusive[n] += 1;
            //}
            ////создаю сет чтоб передав в него все значения вхождений остались чтолько оригинальные
            ////(если число 2  и число 5 попадались по 5 раз, то их вхождения не были оригинальными
            //std::unordered_set<int> set_of_counts{};
            //for (const auto& [num, counts] : exclusive) {
            //    set_of_counts.insert(counts);
            //}
            ////если размер списка вхождений равен размеру самих элементов 
            //// - то каждый элемент входит в arr 
            //if (set_of_counts.size() == exclusive.size()) {
            //    return true;
            //}
            //return false;

            //решение с литкода (быстрее):
            //отсортировать входной массив
            std::ranges::sort(arr);
            //массив для записи кол-ва вхождений
            std::vector<int> count_of_inputs{};
            //счетчик. Так как начну со второго элемента - считаю что первый элемент уже один раз вошёл
            int count{1};
            for (int i = 1; i < arr.size(); ++i) {
                //если элемент с прошлым равны - увеличиваю счетчик
                if (arr[i] == arr[i - 1]) {
                    ++count;
                }
                else { //если не равны - записываю значение счетчика
                    count_of_inputs.push_back(count);
                    //сбрасываю счетчик (1 потому что текущее значение только что встретилось 1 раз)
                    count = 1;
                }
            }
            //для последнего элемента записываю значение
            count_of_inputs.push_back(count);
            //сортирую массив вхождений
            std::ranges::sort(count_of_inputs);
            //и так же проверяю что соседние значения не равны
            for (int i = 1; i < count_of_inputs.size(); ++i) {
                if (count_of_inputs[i] == count_of_inputs[i - 1]) {
                    return false;
                }
            }
            return true;
        }
    };

    class СloseStrings {
    public:
        bool closeStrings(string word1, string word2) {
            //Нужно проверить, что:
            //  -   строки имеют одинаковую длину;
            //  -   в них присутствует одинаковый набор уникальных символов;
            //  -   список частот всех символов одной строки совпадает со списком частот другой строки, если эти частоты отсортировать.
            //    Если все три условия выполнены, строки близкие.Иначе — не близкие.

            //проверить что длины строк равны
            if (word1.size() != word2.size()) {
                return false;
            }
            std::map<char, int> map1, map2;
            //посчитать вхождения символов
            for (int i = 0; i < word1.size(); ++i) {
                map1[word1[i]] += 1;
                map2[word2[i]] += 1;
            }
            //проверяю что буквы те же
            if (map1.size() != map2.size()) {
                return false;
            }
            //одновременно заполняю сеты значений количеств вхождений букв
            std::vector<int>  vecsecond1, vecsecond2 ;
            std::set<char> setfirst1, setfirst2;
            for (auto [first, second] : map1) {
                setfirst1.insert(std::move(first));
                vecsecond1.push_back(std::move(second));
            }
            for (const auto& [first, second] : map2) {
                setfirst2.insert(std::move(first));
                vecsecond2.push_back(std::move(second));
            }
            std::ranges::sort(vecsecond1);
            std::ranges::sort(vecsecond2);

            return (setfirst1 == setfirst2 && vecsecond1 == vecsecond2);
        }
    };

    class EqualPairs {
    public:
        int equalPairs(vector<vector<int>>& grid) {
            //Создаю список строк
            std::vector<std::vector<int>> rows(grid.size(), std::vector<int>(grid.size()));
            std::vector<int> line(grid.size(),0);
            int pares_count{};
            //Записываю все строки
            for (int i = 0; i < grid.size(); ++i) {
                for (int j = 0; j < grid[i].size(); ++j) {
                    line[j] = grid[i][j];
                }
                rows[i] = line;
            }
            //здесь получаю колонки 
            for (int j = 0; j < grid.size(); ++j) {
                for (int i = 0; i < grid[j].size(); ++i) {
                    line[i] = grid[i][j];
                }
                //и сравниваю их со строками, подсчитывая совпадения
                pares_count += std::ranges::count(rows, line);
            }
            return pares_count;
        }
    };

    class RemoveStars {
    public:
        string removeStars(const string& s) {
            //резервируем длину строки для быстроты
            std::string output(s.size(), 'A');
            size_t char_index{};
            //если не звездочка записываем по индексу значение
            for (auto ch : s) {
                if (ch != '*') {
                    output[char_index++] = std::move(ch);
                }//если не звездочка - отходим на 1 индекс назад
                else {
                    --char_index;
                }
            }
            //возвращаем подстроку с 0 индекса размером с char_index (
            output.resize(char_index);
            return output;
        }
    };

    class AsteroidCollision {
    public:
        vector<int> asteroidCollision(const vector<int>& asteroids) {
            std::vector<int> vec_stack(asteroids.size(), asteroids[0]);
            int asteroid_iter{ 0 };
            for (int i = 1; i < asteroids.size(); ++i) {
                //если астероиди летят навстречу
                if (asteroid_iter >= 0 && vec_stack[asteroid_iter] > 0 && asteroids[i] < 0) {
                    //Если левый астероид меньше - уничтожаем его. Текущий астероид чтоб не потерять - сохраняем i на том же месте
                    if (std::abs(vec_stack[asteroid_iter]) < std::abs(asteroids[i])) {
                            --asteroid_iter;
                            --i;
                    } //если равны - оба уничтожаются
                    else if (std::abs(vec_stack[asteroid_iter]) == std::abs(asteroids[i])) {
                            --asteroid_iter;;
                            continue;
                    }//если левый больше - он уничтожил правый и переходим к следующему правому
                }
                else { //если не летят навстречу или итератор -1 (стек пустой) но еще есть правые астероиды - записываем
                    vec_stack[++asteroid_iter] = asteroids[i];
                }
            }
            vec_stack.resize(asteroid_iter+1);
            return vec_stack;
        }
    };

    //Разжатие строки
    class DecodeString {
    private:
        void ClearAll() {
            string_stack_ = {};
            repeat_count_stack_ = {};
            current_count_ = {};
            current_string_ = {};
        }

        void NewWord() {
            string_stack_.push(current_string_);
            repeat_count_stack_.push(current_count_);
            current_string_ = {};
            current_count_ = 0;
        }
        void EraseWord() {
            string_stack_.pop();
            repeat_count_stack_.pop();
        }

    public:
        string decodeString(const string& s) {
            ClearAll();
            for (int i = 0; i < s.size(); ++i) {
                //Встретил цифру — обновил current_number
                if (std::isdigit(s[i])) {
                    //это надо если до этого были добавлены цифры
                    //типа если было 1, то стало 10, к нему добавляем текущую цифру
                    // например 2, и получаем 12. Если было пусто то 0 * 10 = 0, 0 + 2 = 2
                    current_count_ *= 10;
                    current_count_ += s[i] - '0';
                }//Встретил букву — добавил в current_string
                else if (std::isalpha(s[i])) {
                    current_string_ += s[i];
                }//Встретил [ — положил current_string в стек строк, 
                //положил current_number в стек чисел, а сами переменные 
                //current_string и current_number обнулил.
                else if (s[i] == '[') {
                    NewWord();
                }
                else if (s[i] == ']') {
                    //взял кол-во повторений из стека повторений
                    std::string repeated_str{};
                    for (int j = 0; j < repeat_count_stack_.top(); ++j) {
                        //повторил текущую строку нужное кол-во раз
                        repeated_str.append(current_string_);
                    }
                    //добавил эти повторения к верхнему значению стека строк
                    string_stack_.top().append(repeated_str);
                    //полученную строку записал в текущее значение
                    current_string_ = string_stack_.top();
                    //и закрыл скобку, удалив верхние значения стеков
                    EraseWord();
                }
            }
            //возвращать надо текущую строку, в ней сохранена вся последовательность
            return current_string_;
        }

    private:
        std::stack<std::string> string_stack_{};
        std::stack<int> repeat_count_stack_{};
        int current_count_{ 0 };
        std::string current_string_{""};
    };

    //Подсчет элементов в ограничеснной очереди
    //типа сколько было obj за последние t = 3000 миллисекунд
    class RecentCounter {
    public:
        RecentCounter() {}

        int ping(int t) {
            pings_.push(t);
            while (pings_.front() < t - time) {
                pings_.pop();
            }
            return pings_.size();
        }
    private:
        static constexpr int time{ 3000 };
        std::queue<int> pings_{};
    };

    //Бои сенаторов
    class PredictPartyVictory {
    public:
        string predictPartyVictory(const string& senate) {
            //если последующий != предыдущему, то последующий уничтожается
            std::queue<size_t> radiant_senate{};
            std::queue<size_t> dire_senate{};
            //заполняем очереди значениями индекса
            //сенаторы будут сражаться по типу (меньше - победил)
            for (size_t i = 0; i < senate.size(); ++i) {
                if (senate[i] == 'R') {
                    radiant_senate.push(i);
                }
                else {
                    dire_senate.push(i);
                }
            }
            //цикл сражения:
            while (radiant_senate.size() != 0 && dire_senate.size() != 0) {
                //Если у радианта значение меньше - он победил
                if (radiant_senate.front() < dire_senate.front()) {
                    //сенатор из dire уходит
                    dire_senate.pop();
                    //сенатор из radiant переходит в конец очереди
                    //типа берет талон с номером больше чем у последнего (+size() это гарантирует)
                    radiant_senate.push(radiant_senate.front() + senate.size());
                    //затем выходит из начала очереди
                    radiant_senate.pop();
                }//аналогично с сенаторами dire
                else {
                    radiant_senate.pop();
                    dire_senate.push(dire_senate.front() + senate.size());
                    dire_senate.pop();
                }
            }
            //тут просто смотрю в какой очереди остались сенаторы
            return radiant_senate.size() > 0 ? "Radiant" : "Dire";
        }
    };
    using namespace tools;

    //Черепаха и заяц
    class DeleteMiddle {
    public:
        //Эталонный код:
        ListNode* deleteMiddle(tools::ListNode* head) {
            //если элемень только один то возвращаем пустой список
            if (!head->next) {
                return nullptr;
            }

            ListNode* turtle = head;
            ListNode* rabbit = turtle->next->next;

            //Пока rabbit или следующий за ним элементы существуют
            while (rabbit && rabbit->next) {
                //перезаписываем все указатели
                turtle = turtle->next;
                rabbit = rabbit->next->next;
            }
            //как только быстрый указатель упрётся в пустоту
            //у текущей черепахи перекидываем указатель next дальше
            turtle->next = turtle->next->next;
            return head;
        }
        ////мой код:
        //ListNode* deleteMiddle(ListNode* head) {
        //    ListNode* faster = head;
        //    ListNode* slower = head;
        //    ListNode* previous = head;

        //    //если элемент один то вернуть пустой список
        //    if (faster->next == nullptr) {
        //        //delete head;
        //        return nullptr;
        //    }
        //    //Пока faster или следующий за ним элементы существуют
        //    while (faster != nullptr && faster->next != nullptr) {
        //        //перезаписываем все указатели
        //        previous = slower;
        //        slower = slower->next;
        //        faster = faster->next->next;
        //    }
        //    //как только быстрый указатель упрётся в пустоту
        //    // previous должен начать указывать через один элемент
        //    // а пропущенный элемент лучше удалить
        //    previous->next = slower->next;
        //    //delete slower;
        //    return head;
        //}
    };

    //разделение на четные и нечетные индексы
    class OddEvenList {
    public:
        ListNode* oddEvenList(ListNode* head) {
            //если список содержит до 2-х элементов включительно - возвращаем что есть
            if (!head || !head->next || !head->next->next) {
                return head;
            }
            //нужно 3 указателя: на список нечетных элементов
            ListNode* odd = head;
            //и на список четных элементов
            ListNode* even = odd->next;
            //и начало списка четных
            ListNode* even_head = even;

            //пока четный и следующий за ним элементы есть (потому что ближе к краю именно четный)
            while (even && even->next) {
                //Нечетному записываем в next элемент через один
                odd->next = odd->next->next;
                //обновляем указатель
                odd = odd->next;

                //то же самое делаем для четного
                even->next = even->next->next;
                even = even->next;
            }

            //получилось 2 списка. Объединяем. Для этого последнему 
            // нечетному указываем что следующий элемент - первый из четных
            odd->next = even_head;

            //возвращаем head, т.к. из-за работы с указателями манипуляции были произведены и с ним
            return head;
        }
    };


    //разворот списка
    class ReverseList {
    public:
        ListNode* reverseList(ListNode* head) {
            //Если пустой или всего 1 элемент - нечего инвертировать
            if (head == nullptr || head->next == nullptr) {
                return head;
            }
            //нужны 3 указателя
            ListNode* previous{ nullptr };
            ListNode* current = head;
            ListNode* next = current->next;
            //задаем текущему элементу предыдущий как следующий
            //т.к. реальный следующий уже сохранен в next
            current->next = previous;
            //пока есть куда идти
            while (next) {
                //сдвигаем все элементы вправо
                previous = current;
                current = next;
                next = next->next;
                //у предыдущего next (текущий current) еще не поменян указатель на следующий.
                //меняем
                current->next = previous;
            }
            head = current;
            return head;
        }
    };

    //сложение пар противоположностей в односвязном списке
    //Если использовать зайца и черепаху для поиска середины
    //затем использовать разворот списка с середины
    //то получится быстро :)
    class PairSum {
    public:
        //==== ЭТАЛОННОЕ РЕШЕНИЕ ====
        //Метод разворота из предыдущего задания
        ListNode* reverseList(ListNode* head) {
            //Если пустой или всего 1 элемент - нечего инвертировать
            if (head == nullptr || head->next == nullptr) {
                return head;
            }
            //нужны 3 указателя
            ListNode* previous{ nullptr };
            ListNode* current = head;
            ListNode* next = current->next;
            //задаем текущему элементу предыдущий как следующий
            //т.к. реальный следующий уже сохранен в next
            current->next = previous;
            //пока есть куда идти
            while (next) {
                //сдвигаем все элементы вправо
                previous = current;
                current = next;
                next = next->next;
                //у предыдущего next (текущий current) еще не поменян указатель на следующий.
                //меняем
                current->next = previous;
            }
            head = current;
            return head;
        }

        int pairSum(ListNode* head) {
            //Здесь используем зайца и черепаху
            ListNode* i = head;
            ListNode* j = head->next;
            while (j->next) {
                j = j->next->next;
                i = i->next;
            }

            //i->next передаем, т.к. черепаха указывала на i/2, 
            // это последний элемент из левой половины
            // а нам нужен первый из правой половины
            //и так мы получаем указатель на перевернутую правую половину
            ListNode* reversed_half = reverseList(i->next);
            int max_summ{ 0 };
            int current_summ{ 0 };

            //пока эта половина не закончится ищу максимальную сумму
            while (reversed_half) {
                max_summ = std::max(max_summ, head->val + reversed_half->val);
                head = head->next;
                reversed_half = reversed_half->next;
            }
            return max_summ;

            ////==== Это мое решение с массивом. ==== Не сильно то и медленнее
            //// Если заранее рассчитать размер вектора - то это не ускорит тесты, т.к.
            //// для этого надо будет 2 раза пройтись по списку
            //std::vector<int> values;
            //ListNode* pointer = head;
            //while (head) {
            //    values.push_back(head->val);
            //    head = head->next;
            //}
            //int max_summ{ 0 };
            //int current_summ{ 0 };
            //for (int i = 0; i < values.size() / 2; ++i) {
            //    current_summ = values[i] + values[values.size() - 1 - i];
            //    max_summ = std::max(max_summ, current_summ);
            //}
            //return max_summ;
        }
    };


    //рекурсивный DFS
    class MaxDepth {
    public:
        int maxDepth(TreeNode* root) {
            //если узел пустой возвращаем ноль
            if (!root) {
                return 0;
            }
            //рекурсивно проходим по левым и правым веткам
            int left_depth = maxDepth(root->left);
            int right_depth = maxDepth(root->right);

            //а это как раз и выдает ответ. 
            //Возвращаем глубину 1 этой ноды + максимальную из глубин левых или правых нод
            return 1 + std::max(left_depth, right_depth);
        }
    };
}//namespace problems

namespace tests {
    void mergeAlternatelyTest() {
        problems::MergeAlternately solution1768{};
         assert(solution1768.mergeAlternately("abc"s, "pqr"s) == "apbqcr");
         assert(solution1768.mergeAlternately("ab"s, "pqrs"s) == "apbqrs");
         assert(solution1768.mergeAlternately("abcd"s, "pq"s) == "apbqcd");
         std::cout << "Merge Strings Alternately is OK" << std::endl;
    }

    void gcdOfStringsTest() {
        problems::GCDOfStrings solution1071{};
        assert(solution1071.gcdOfStrings("ABCABC", "ABC") == "ABC");
        assert(solution1071.gcdOfStrings("ABABAB", "ABAB") == "AB");
        assert(solution1071.gcdOfStrings("LEET", "CODE") == "");
        assert(solution1071.gcdOfStrings("AAAAAB", "AAA") == "");
        assert(solution1071.gcdOfStrings("ABABABAB", "ABAB") == "ABAB");
        std::cout << "Greatest Common Divisor of Strings is OK" << std::endl;
    }

    void kidsWithCandiesTest() {
        problems::KidsWithCandies solution1431{};
        std::vector<bool> expected{ true, true, true, false, true };
        assert(solution1431.kidsWithCandies({ 2,3,5,1,3 }, 3) == expected);
        expected = { true,false,false,false,false };
        assert(solution1431.kidsWithCandies({ 4,2,1,1,2 }, 1) == expected);
        expected = { true,false,true };
        assert(solution1431.kidsWithCandies({ 12,1,12 }, 3) == expected);
        std::cout << "Kids With the Greatest Number of Candies is OK" << std::endl;
    }

    void canPlaceFlowersTest() {
        problems::CanPlaceFlowers solution605{};
        vector<int> input{ 1,0,0,0,1 };
        assert(solution605.canPlaceFlowers(input, 1) == true);
        assert(solution605.canPlaceFlowers(input, 2) == false);
        std::cout << "Can Place Flowers is OK" << std::endl;
    }

    void reverseVowelsTest() {
        problems::ReverseVowels solution345{};
        assert(solution345.reverseVowels("IceCreAm") == "AceCreIm");
        assert(solution345.reverseVowels("leetcode") == "leotcede");
        std::cout << "CReverse Vowels of a String is OK" << std::endl;
    }

    void reverseWordsTest() {
        problems::ReverseWords solution151{};
        assert(solution151.reverseWords("the sky is blue") == "blue is sky the");
        assert(solution151.reverseWords("  hello world  ") == "world hello");
        assert(solution151.reverseWords("a good   example") == "example good a");
        std::cout << "Reverse Words in a String is OK" << std::endl;
    }

    void productExceptSelf() {
        problems::ProductExceptSelf solution238{};
        std::vector<int> except{ 24,12,8,6 };
        assert(solution238.productExceptSelf({ 1, 2, 3, 4 }) == except);
        except = { 0,0,9,0,0 };
        assert(solution238.productExceptSelf({ -1, 1, 0, -3, 3 }) == except);
        std::cout << "Product of Array Except Self is OK" << std::endl;
    }

    void increasingTriplet() {
        problems::IncreasingTriplet solution334{};
        assert(solution334.increasingTriplet({ 1, 2, 3, 4, 5 }) == true);
        assert(solution334.increasingTriplet({ 5, 4, 3, 2, 1 }) == false);
        assert(solution334.increasingTriplet({ 2, 1, 5, 0, 4, 6 }) == true);
        std::cout << "Increasing Triplet Subsequence is OK" << std::endl;
    }

    void compressTest() {
        problems::Сompressor solution443{};
        vector<char> chars = { 'a','a','b','b','c','c','c' };
        assert(solution443.compress(chars) == 6);
        chars = { 'a' };
        assert(solution443.compress(chars) == 1);
        chars = { 'a','b','b','b','b','b','b','b','b','b','b','b','b' };
        assert(solution443.compress(chars) == 4);
        std::cout << "String Compression is OK" << std::endl;
    }

    void moveZeroesTest() {
        problems::MoveZeroes solution283{};
        std::vector<int> input{ 0,1,0,3,12 };
        solution283.moveZeroes(input);
        std::vector<int> except{ 1,3,12,0,0 };
        assert(input == except);
        input = { 0 };
        except = { 0 };
        assert(input == except);
        std::cout << "Move Zeroes is OK" << std::endl;
    }

    void isSubsequenceTest() {
        problems::IsSubsequence solution392{};
        std::string input{ "abc" };
        std::string t{ "ahbgdc" };
        assert(solution392.isSubsequence(input, t));
        input = "axc";
        t = "ahbgdc";
        assert(!solution392.isSubsequence(input, t));
        input = "b";
        t = "c";
        assert(!solution392.isSubsequence(input, t));
        input = "acb";
        t = "ahbgdc";
        assert(!solution392.isSubsequence(input, t));
        std::cout << "Is Subsequence is OK" << std::endl;
    }

    void maxAreaTest() {
        problems::MaxArea solution11{};
        std::vector<int> height{ 1,8,6,2,5,4,8,3,7 };
        assert(solution11.maxArea(height) == 49);
        height = { 1,1 };
        assert(solution11.maxArea(height) == 1);
        std::cout << "Container With Most Water is OK" << std::endl;
    }

    void maxOperationsTest() {
        problems::MaxOperations solution1679{};
        std::vector<int> input{ 1,2,3,4 };
        int k = 5;
        assert(solution1679.maxOperations(input, k) == 2);
        input = { 3, 1, 3, 4, 3 };
        k = 6;
        assert(solution1679.maxOperations(input, k) == 1);
        std::cout << "Max Number of K-Sum Pairs is OK" << std::endl;
    }

    void findMaxAverageTest() {
        problems::FindMaxAverage solution643{};
        std::vector<int> input{ 1,12,-5,-6,50,3 };
        int k = 4;
        double etalon{ 12.75000 };
        assert(solution643.findMaxAverage(input, k) == etalon);
        input = { 5 };
        k = 1;
        etalon = 5.00000;
        assert(solution643.findMaxAverage(input, k) == etalon);
        std::cout << "Maximum Average Subarray I is OK" << std::endl;
    }

    void maxVowelsTest() {
        problems::MaxVowels solution1456{};
        std::string s{ "abciiidef" };
        int k = 3;
        assert(solution1456.maxVowels(s, k) == 3);
        s = "aeiou";
        k = 2;
        assert(solution1456.maxVowels(s, k) == 2);
        s = "leetcode";
        k = 3;
        assert(solution1456.maxVowels(s, k) == 2);
        std::cout << "Maximum Number of Vowels in a Substring of Given Length is OK" << std::endl;
    }

    void longestOnesTest(){
        problems::LongestOnes solution1004 {};
        std::vector<int> nums{ 1,1,1,0,0,0,1,1,1,1,0 };
        int k = 2;
        int excepted_output = 6;
        assert(solution1004.longestOnes(nums, k) == excepted_output);
        nums = { 0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1 };
        k = 3;
        excepted_output = 10;
        assert(solution1004.longestOnes(nums, k) == excepted_output);
        std::cout << "Max Consecutive Ones III is OK" << std::endl;
    }

    void longestSubarrayTest() {
        problems::LongestSubarray solution1493{};
        std::vector<int> nums{ 1,1,0,1 };
        int output = 3;
        assert(solution1493.longestSubarray(nums) == output);
        nums = { 0,1,1,1,0,1,1,0,1 };
        output = 5;
        assert(solution1493.longestSubarray(nums) == output);
        nums = { 1,1,1 };
        output = 2;
        assert(solution1493.longestSubarray(nums) == output);
        std::cout << "Longest Subarray of 1's After Deleting One Element is OK" << std::endl;
    }

    void largestAltitudeTest() {
        problems::LargestAltitude solution1732{};
        std::vector<int> gain{ -5,1,5,0,-7 };
        int expected{ 1 };
        assert(solution1732.largestAltitude(gain) == expected);
        gain = { -4,-3,-2,-1,4,3,2 };
        expected = 0;
        assert(solution1732.largestAltitude(gain) == expected);
        std::cout << "Find the Highest Altitude is OK" << std::endl;
    }

    void pivotIndexTest() {
        problems::PivotIndex solution724{};
        std::vector<int> nums{ 1,7,3,6,5,6 };
        int expected = 3;
        assert(solution724.pivotIndex(nums) == expected);
        nums = { 1,2,3 };
        expected = -1;
        assert(solution724.pivotIndex(nums) == expected);
        nums = { 2,1,-1 };
        expected = 0;
        assert(solution724.pivotIndex(nums) == expected);
        std::cout << "Find Pivot Index is OK" << std::endl;
    }

    void findDifference() {
        problems::FindDifference solution2215{};
        std::vector<int> nums1{ 1,2,3 }, nums2{ 2,4,6 };
        std::vector<std::vector<int>> expected{ {1,3},{4,6} };
        assert(solution2215.findDifference(nums1, nums2) == expected);
        nums1 = { 1,2,3,3 };
        nums2 = { 1,1,2,2 };
        expected = { {3},{} };
        assert(solution2215.findDifference(nums1, nums2) == expected);
        std::cout << "Find the Difference of Two Arrays is OK" << std::endl;
    }

    void uniqueOccurrencesTest() {
        problems::UniqueOccurrences solution1207{};
        std::vector<int> arr{ 1,2,2,1,1,3 };
        bool expected = true;
        assert(solution1207.uniqueOccurrences(arr) == expected);
        arr = { 1,2 };
        expected = false;
        assert(solution1207.uniqueOccurrences(arr) == expected);
        arr = { -3,0,1,-3,1,1,1,-3,10,0 };
        expected = true;
        assert(solution1207.uniqueOccurrences(arr) == expected);
        std::cout << "Unique Number of Occurrences is OK" << std::endl;
    }

    void closeStringsTest() {
        problems::СloseStrings solution1657{};
        std::string word1{ "abc" };
        std::string word2{ "bca" };
        bool expected{ true };
        assert(solution1657.closeStrings(word1, word2) == expected);
        word1 = "a";
        word2 = "aa";
        expected = false;
        assert(solution1657.closeStrings(word1, word2) == expected);
        word1 = "cabbba";
        word2 = "abbccc";
        expected = true;
        assert(solution1657.closeStrings(word1, word2) == expected);
        std::cout << "Determine if Two Strings Are Close is OK" << std::endl;
    }

    void equalPairsTest() {
        problems::EqualPairs solution2352{};
        std::vector<std::vector<int>> grid{ {3, 2, 1}, {1, 7, 6}, { 2, 7, 7 } };
        int excepted{ 1 };
        assert(solution2352.equalPairs(grid) == excepted);
        grid = { {3,1,2,2},{1,4,4,5},{2,4,2,2},{2,4,2,2} };
        excepted = 3;
        assert(solution2352.equalPairs(grid) == excepted);
        grid = { {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                 {2, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                 {3, 3, 3, 4, 5, 6, 7, 8, 9, 10},
                 {4, 4, 4, 4, 5, 6, 7, 8, 9, 10},
                 {5, 5, 5, 5, 5, 6, 7, 8, 9, 10},
                 {6, 6, 6, 6, 6, 6, 7, 8, 9, 10},
                 {7, 7, 7, 7, 7, 7, 7, 8, 9, 10},
                 {8, 8, 8, 8, 8, 8, 8, 8, 9, 10},
                 {9, 9, 9, 9, 9, 9, 9, 9, 9, 10},
                 {10,10,10,10,10,10,10,10,10,10} };
        excepted = 10;
        assert(solution2352.equalPairs(grid) == excepted);
        std::cout << "Equal Row and Column Pairs is OK" << std::endl;
    }

    void removeStarsTest() {
        problems::RemoveStars solution2390{};
        std::string s{ "leet**cod*e" };
        std::string expected{ "lecoe" };
        assert(solution2390.removeStars(s) == expected);
        s = "erase*****";
        expected = "";
        assert(solution2390.removeStars(s) == expected);
        std::cout << "Removing Stars From a String is OK" << std::endl;
    }

    void asteroidCollisionTests() {
        problems::AsteroidCollision solution735{};
        std::vector<int> asteroids{ 5,10,-5 };
        std::vector<int> expected{ 5,10 };
        assert(solution735.asteroidCollision(asteroids) == expected);
        asteroids = { 8,-8 };
        expected = {};
        assert(solution735.asteroidCollision(asteroids) == expected);
        asteroids = { 10,2,-5 };
        expected = { 10 };
        assert(solution735.asteroidCollision(asteroids) == expected);
        asteroids = { 3,5,-6,2,-1,4 };
        expected = { -6,2,4 };
        assert(solution735.asteroidCollision(asteroids) == expected);
        std::cout << "Asteroid Collision is OK" << std::endl;
    }

    void decodeStringTest() {
        problems::DecodeString solution394{};
        std::string s{ "3[a]2[bc]" };
        std::string expected{ "aaabcbc" };
        assert(solution394.decodeString(s) == expected);
        s = "3[a2[c]]";
        expected = "accaccacc";
        assert(solution394.decodeString(s) == expected);
        s = "2[abc]3[cd]ef";
        expected = "abcabccdcdcdef";
        assert(solution394.decodeString(s) == expected);
        std::cout << "Decode String is OK" << std::endl;
    }

    void recentCounterTest() {
        problems::RecentCounter* recent_counter = new problems::RecentCounter();
        std::vector<int> answer{};
        answer.push_back(recent_counter->ping(1));
        answer.push_back(recent_counter->ping(100));
        answer.push_back(recent_counter->ping(3001));
        answer.push_back(recent_counter->ping(3002));
        std::vector<int> expected{ 1,2,3,3 };
        assert(answer == expected);
        std::cout << "Number of Recent Calls is OK" << std::endl;
    }

    void predictPartyVictoryTest() {
        problems::PredictPartyVictory solution649{};
        std::string input{ "RD" };
        std::string output{ "Radiant" };
        assert(solution649.predictPartyVictory(input) == output);
        input = "RDD";
        output = "Dire";
        assert(solution649.predictPartyVictory(input) == output);
        std::cout << "Dota2 Senate is OK" << std::endl;
    }

    void deleteMiddleTest() {
        problems::DeleteMiddle solution2095{};
        tools::ListConverter converter{};

        // --- Пример 1 ---
        std::vector<int> input = { 1, 3, 4, 7, 1, 2, 6 };
        std::vector<int> expected = { 1, 3, 4, 1, 2, 6 };

        tools::ListNode* head = converter.createList(input);
        tools::ListNode* result = solution2095.deleteMiddle(head);

        assert(converter.listToVector(result) == expected);
        std::cout << "Test 1 passed" << std::endl;


        // --- Пример 2 ---
        input = { 1, 2, 3, 4 };
        expected = { 1, 2, 4 };

        head = converter.createList(input);
        result = solution2095.deleteMiddle(head);

        assert(converter.listToVector(result) == expected);
        std::cout << "Test 2 passed" << std::endl;


        // --- Пример 3 ---
        input = { 2, 1 };
        expected = { 2 };

        head = converter.createList(input);
        result = solution2095.deleteMiddle(head);

        assert(converter.listToVector(result) == expected);
        std::cout << "Test 3 passed" << std::endl;


        // --- Граничный случай: список из 1 элемента ---
        input = { 1 };
        expected = {}; // Пустой вектор

        head = converter.createList(input);
        result = solution2095.deleteMiddle(head);

        assert(converter.listToVector(result) == expected);
        std::cout << "Test 4 (Edge case) passed" << std::endl;

        std::cout << "All Delete Middle Node tests are OK!" << std::endl;
    }

    void oddEvenListTest() {
        problems::OddEvenList solution328{};
        tools::ListConverter converter{};

        // Тест: Пустой список
        std::vector<int> input = {};
        std::vector<int> expected = {};

        tools::ListNode*  head = converter.createList(input);
        tools::ListNode*  result = solution328.oddEvenList(head);

        assert(converter.listToVector(result) == expected);
        std::cout << "Тест с пустым списком пройден" << '\n';

        // Тест: Список из 1 элемента
        input = { 1 };
        expected = { 1 };

        head = converter.createList(input);
        result = solution328.oddEvenList(head);

        assert(converter.listToVector(result) == expected);
        std::cout << "Тест со списком из 1 элемента пройден" << '\n';

        // Тест: Список из 2 элементов
        input = { 1, 2 };
        expected = { 1, 2 }; // 1 - нечетный индекс, 2 - четный индекс

        head = converter.createList(input);
        result = solution328.oddEvenList(head);

        assert(converter.listToVector(result) == expected);
        std::cout << "Тест со списком из 2 элементов пройден" << '\n';

        input = { 1,2,3,4,5 };
        expected = { 1,3,5,2,4 };

        head = converter.createList(input);
        result = solution328.oddEvenList(head);
        tools::PrintVector(converter.listToVector(result));
        assert(converter.listToVector(result) == expected);

        std::cout << "Тест с нечетным количеством элементов пройден" << '\n';

        input = { 2,1,3,5,6,4,7 };
        expected = { 2,3,6,7,1,5,4 };

        head = converter.createList(input);
        result = solution328.oddEvenList(head);

        assert(converter.listToVector(result) == expected);

        std::cout << "Тест с четным количеством элементов пройден" << '\n';
        std::cout << "Odd Even Linked List are OK!" << std::endl;
    }

    void reverseListTest() {
        problems::ReverseList solution206{};
        tools::ListConverter converter{};

        std::vector<int> input{ 1,2,3,4,5 };
        std::vector<int> expected{ 5,4,3,2,1 };

        tools::ListNode* head = converter.createList(input);
        tools::ListNode* result = solution206.reverseList(head);
        
        auto resultvec = converter.listToVector(result);
        tools::PrintVector(resultvec);
        assert(resultvec == expected);

        input = { 1,2 };
        expected = { 2,1 };

        head = converter.createList(input);
        result = solution206.reverseList(head);

        assert(converter.listToVector(result) == expected);

        input = { 1 };
        expected = { 1 };

        head = converter.createList(input);
        result = solution206.reverseList(head);

        assert(converter.listToVector(result) == expected);

        input = {};
        expected = {};

        head = converter.createList(input);
        result = solution206.reverseList(head);

        assert(converter.listToVector(result) == expected);

        std::cout << "Reverse Linked List are OK!" << std::endl;
    }

    void pairSumTest() {
        problems::PairSum solution2130{};
        tools::ListConverter converter{};

        std::vector<int> input;
        int expected;
        tools::ListNode* head;
        int result;

        input = { 5, 4, 2, 1 };
        expected = 6;
        head = converter.createList(input);
        result = solution2130.pairSum(head);
        assert(result == expected);
        std::cout << "Тест [5, 4, 2, 1] прошел\n";

        input = { 4, 2, 2, 3 };
        expected = 7;
        head = converter.createList(input);
        result = solution2130.pairSum(head);
        assert(result == expected);
        std::cout << "Тест [4, 2, 2, 3] прошел\n";

        input = { 1, 100000 };
        expected = 100001;
        head = converter.createList(input);
        result = solution2130.pairSum(head);
        assert(result == expected);
        std::cout << "Тест [1, 100000] прошел\n";

        std::cout << "Maximum Twin Sum of a Linked List tests are OK!" << std::endl;
    }

    void maxDepthTest() {
        using namespace tools;
        problems::MaxDepth solution104{};

        TreeNode* root = new TreeNode(3 , new TreeNode(9), new TreeNode(20));
        root->right->left = new TreeNode(15);
        root->right->right = new TreeNode(7);
        int excepted = 3;
        assert(solution104.maxDepth(root) == excepted);

        root = new TreeNode(1, nullptr, new TreeNode(2));
        excepted = 2;

        assert(solution104.maxDepth(root) == excepted);
        std::cout << "Maximum Depth of Binary Tree is OK!" << std::endl;
    }
}//namespace tests



int main(){
    //tests::mergeAlternatelyTest();
    //tests::gcdOfStringsTest();
    //tests::kidsWithCandiesTest();
    //tests::canPlaceFlowersTest();
    //tests::reverseVowelsTest();
    //tests::reverseWordsTest();
    //tests::productExceptSelf();
    //tests::increasingTriplet();
    //tests::compressTest();
    //tests::moveZeroesTest();
    //tests::isSubsequenceTest();
    //tests::maxAreaTest();
    //tests::maxOperationsTest();
    //tests::findMaxAverageTest();
    //tests::maxVowelsTest();
    //tests::longestOnesTest();
    //tests::longestSubarrayTest();
    //tests::largestAltitudeTest();
    //tests::pivotIndexTest();
    //tests::findDifference();
    //tests::uniqueOccurrencesTest();
    //tests::closeStringsTest();
    //tests::equalPairsTest();
    //tests::removeStarsTest();
    //tests::asteroidCollisionTests();
    //tests::decodeStringTest();
    //tests::recentCounterTest();
    //tests::predictPartyVictoryTest();
    //tests::deleteMiddleTest();
    //tests::oddEvenListTest();
    //tests::reverseListTest();
    //tests::pairSumTest();
    tests::maxDepthTest();
}
