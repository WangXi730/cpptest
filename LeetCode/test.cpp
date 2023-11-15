#include"LeetCodeTools.hpp"
#include"Type.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<forward_list>

using TreeNode = wx::TreeNode<int>;
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>


//int main() {
//    Integer a("-67899");
//    Integer b("6789");
//
//    // 测试加法
//    Integer sum = a + b;
//    std::cout << "Sum: " << sum << std::endl;
//
//    // 测试减法
////    Integer difference = a - b;
//    Integer difference = a;
//    difference -= b;
//    std::cout << "Difference: " << difference << std::endl;
//
//    // 测试乘法
//    Integer product = a * b;
//    std::cout << "Product: " << product << std::endl;
//
//    // 测试除法
//    Integer quotient = a / b;
//    std::cout << "Quotient: " << quotient << std::endl;
//
//    // 测试取模
//    Integer remainder = a % b;
//    std::cout << "Remainder: " << remainder << std::endl;
//
//    //测试比较
//    if (a <= b) {
//        std::cout << "a <= b" << std::endl;
//    }
//    else {
//        std::cout << "a > b" << std::endl;
//    }
//
//    //自增自减
//    for (int i = 0; i < 10; ++i) {
//        std::cout << a++ << std::endl;
//    }
//    for (int i = 0; i < 10; ++i) {
//        std::cout << a-- << std::endl;
//    }
//    for (int i = 0; i < 10; ++i) {
//        a += 2ll;
//        std::cout << a << std::endl;
//    }
//    for (int i = 0; i < 10; ++i) {
//        a -= 2;
//        std::cout << a << std::endl;
//    }
//    return 0;
//}


struct A { int a; };
struct B : A
{
	void func() {
		std::cout << this->a;
	}
};
int main() {
    // 创建两个分数，使用 int 类型
    Fraction<int> frac1(3, 4);
    Fraction<int> frac2(1, 2);

    // 加法
    Fraction<int> result_add = frac1 + frac2;
    std::cout << "Addition: " << result_add << std::endl;

    // 减法
    Fraction<int> result_subtract = frac1 - frac2;
    std::cout << "Subtraction: " << result_subtract << std::endl;

    // 乘法
    Fraction<int> result_multiply = frac1 * frac2;
    std::cout << "Multiplication: " << result_multiply << std::endl;

    // 除法
    Fraction<int> result_divide = frac1 / frac2;
    std::cout << "Division: " << result_divide << std::endl;

    //// 创建两个分数，使用 double 类型
    //Fraction<double> frac3(1.5, 2.5);
    //Fraction<double> frac4(0.5, 1.5);

    //// 加法
    //Fraction<double> result_add_double = frac3 + frac4;
    //std::cout << "Addition (double): " << result_add_double << std::endl;

    //创建两个数字
    Figure f1;
    Figure f2(10);
    Figure f3(3,7);
    std::cout << f1 << std::endl;
    std::cout << f2 << std::endl;
    std::cout << f3 << std::endl;

    return 0;
}


//int main() {
//	std::string s = "[[[1,3 ,4],[],[2,4,5,4]],[[2,2,3],[1,2,3]]]";
//	std::vector<std::vector<std::vector<int>>> sv;
//	std::list<std::list<std::list<int>>> sl;
//	wx::create(s, sv);
//	wx::create(s, sl);
//	std::string s1 = "[0,1,2,3,4,5,null,7,8]";
//	wx::TreeNode<long double>* root;
//	wx::create(s1, root);
//	std::vector<wx::SigleListNode<std::list<int>>*> slv;
//	wx::create(s, slv);
//	wx::SigleListNode<std::vector<std::list<int>>>* vsl = nullptr;
//	wx::create(s, vsl);
//
//
//	std::string s_sv;
//	wx::save(s_sv, sv);
//	std::string s_sl;
//	wx::save(s_sl, sv);
//	std::string s1_root;
//	wx::save(s1_root, root);
//	//
//	std::string s_slv;
//	wx::save(s_slv, slv);
//	std::string s_vsl;
//	wx::save(s_vsl, vsl);
//
//	return 0;
//}

