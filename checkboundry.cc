float checkInput(float a) {
while (a <= 0) {
std::cout << "The number you entered is not valid, please enter a positive       number :";
std::cin.clear();
std::cin.ignore(10000, '\n');
std::cin >> a;
}
    return a;
}
