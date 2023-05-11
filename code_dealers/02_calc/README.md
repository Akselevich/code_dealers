# 🚀 Grapghical calculator 🚀
Graphing calculator is a terminal calculator program with the ability to plot graphs. The graphics part is based on the [FTXUI](https://github.com/ArthurSonzogni/FTXUI) library. Expression evaluation was implemented using the [tinyexpr](https://github.com/codeplea/tinyexpr) library.
## 🔥 We have implemented the following functionality 🔥:

- [x]  Working app code 🩻
- [x]  Basic arithmetic operations support 🔥
- [ ]  Mathematical and physical constants support 
- [ ]  Plotting support 

## Code examples for the following functionality:

### Basic arithmetic operations support:
        
```c++
std::string Logic::process_math() {
    if (expression.empty())
        return "";
    std::string input_ss;
    input_ss.append(expression);
    std::string output_ss;
    double a = te_interp(input_ss.c_str(), 0);
    output_ss = std::to_string(a); //kostili, for reading pointless point
    output_ss.erase(output_ss.find_last_not_of('0') + 1, std::string::npos);
    if (output_ss.back() == '.')
        output_ss.replace(output_ss.find('.'), output_ss.find('.') + 1, "");

    return output_ss;
}
```