#include <sstream>
#include <fstream>
#include <iostream>
#include "Tokenizer/TokenStream.hpp"
#include "Tokenizer/Token.hpp"
#include "Nodes/INode.hpp"
#include "Parser/Parser.hpp"
#include "Visitors/GenerateCode.hpp"

int main()
{
    //std::stringstream ss("a +b*c + d + -(c -d) * (a_x+ b_x * deltaT)");
    //std::stringstream ss("a +b*c + d");
    //std::stringstream ss(" int main(int a, /*int b,*/ int c) { return; return a; base(2, 3, 5, 7, 11); return 2 + 3 * 5 ^ 7 * 11;}");

    //std::stringstream ss("2^(2 * 2 + 2) + 3 ^ (2 + 3) * 10");
    //std::stringstream ss("2 + 2 ^ 2 ^ 3 * 10");
    //std::stringstream ss("2 ^ 8 + 10 * 2 ^ 3");
    //std::stringstream ss("2^2^2^2");
    //std::stringstream ss("2.5 3 4.555 555.2 12");
    //std::stringstream ss("0.7 + 10 + 17 - 0.6");
    //std::stringstream ss("0.1 ^ 0.1");

    //std::stringstream ss("void main() {int a; a = 5; print(a); return; }");
    //std::stringstream ss("void main() {int a; int b; a = 5;b = 7; a =a + b; print(a); print(b); return;}");
    //std::stringstream ss("void main() {int a; double b; a = 5; b = 0.001; print(a); print(b); return;}");
    //std::stringstream ss("int foo(int a, int b) {return a + b;}  void main() {int a; a = foo(17, 7); print(a); return; }");

    //std::stringstream ss("void main() {int a; a = 5; int b; b = 10; if (a > b) { print(a);}; return; }");
    //std::stringstream ss("void main() { int a; a = 5; int b; b = 10; if (a <= b) { print(a); } else { print(b); }; return; }");

    std::fstream ss("sqrt1.txt", std::fstream::in);

    TokenStream tokenStream(ss);

    Parser parser(tokenStream);
    std::shared_ptr<INode> program = nullptr;
    program = parser.parse();

    GenerateCode generateCode;
    program->accept(&generateCode);
    std::cout << generateCode.getCode() << std::endl;

    return 0;
}
