# Intent of the `Args` class

The `Args` class is intended to make the use of `argc` and `argv` command-line parameters of a C++ program easy. It
supports both *named* parameters and *order-based* parameters.

# How to use an Args object

Begin by instantiating your `Args` object:
```c++
int main(int argc, char* argv[])
{
	Args args(argc, argv);
	/* ... */
```
You can then get command-line parameter values either using order or names (for named parameters).
Let us suppose your program is called `animal` and that it needs 4 parameters: `kind` of type `string`, `nLegs` of type
`int`, `weight` of type `double` and `isMale` of type `bool`; suppose your command-line looks like this:

```
animal dog 4 7.8 yes
```
You can read your parameters in the program using their order:
```c++

int main(int argc, char* argv[])
{
	Args args(argc, argv);

	std::string kind = "undefined";
	int nLegs = 0;
	double weight = 0.0;
	bool isMale = false;

	args >> kind >> nLegs >> weight >> isMale;
```

However, even if it takes a longer command-line, it is probably more convenient for clarity of both command-line and
code to use named parameters, in which case the command-line will look like:

```
animal kind=dog nLegs=4 weight=7.8 isMale=yes
```
or like:

```
animal --kind dog --nLegs 4 --weight 7.8 --isMale yes
```
or event a mixture of these syntaxes and in any order (and using `true` or `1` instead of `yes` for the boolean value):

```
animal  --nLegs 4 --kind=dog isMale=true --weight 7.8
```

In you C++ code, you can the read-out of named parameters is more concise as it allows both the declaration and the
initialization of each variable in a single line:

```c++
int main(int argc, char* argv[])
{
	Args args(argc, argv);

	std::string kind = args("kind");
	int nLegs = args("nLegs");
	double weight = args("weight");
	bool isMale = args("isMale");

```
It should be noted that even if you use named parameters in your command-line, you still can read them out by order
(i.e. by using chained `>>` operator on your `Args` object).


