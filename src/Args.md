# Intent of the `Args` class

The `Args` class is intended to make the use of `argc` and `argv` command-line parameters of a C++ program easy. It
supports both named parameters and order-based parameters.

# How to use an Args object

Begin by instantiating your `Args` object:
```c++
int main(int argc, char* argv[])
{
	Args args(argc, argv);
}
```
