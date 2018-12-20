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

Let us suppose your program is called `animal` and that it needs 4 parameters: **`kind`** of type `string`, **`nLegs`** of type
`int`, **`weight`** of type `double` and **`isMale`** of type `bool`.

## Read-out by order

Suppose your command-line looks like this:

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

## Read-out by name

Even if it calls for a longer command-line, it is probably more convenient for clarity of both command-line and
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

In your C++ code, your read-out of named parameters is more concise as it allows both the declaration and the
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
**CAUTION**: Because of instrinsic limitations relating to the assignment operator in C++ `std::string`, compilation
will fail when a string variable is first declared and initialized later. To avoid this, either a call with default
value should be used (see further) or the item returned by the parentheses call on the `Args` object must be explicitly
converted to `std::string`:

```c++
int main(int argc, char* argv[])
{
	Args args(argc, argv);
	std::string kind; // declaration of string variable 'kind'
	/* . . . */

	kind = args("kind").convert<std::string>(); // parsing variable 'kind' value from command-line parameter
	/* . . . */
```

An alternative way is to use the left shift operator `<<` instead of the assignment operator; no explicit conversion is
need in that case:

```c++
int main(int argc, char* argv[])
{
	Args args(argc, argv);
	std::string kind; // declaration of string variable 'kind'
	/* . . . */

	kind << args("kind"); // parsing variable 'kind' value from command-line parameter
	/* . . . */
```

It should be noted that even if you use named parameters in your command-line, you can still read them out by order
(i.e. by using chained `>>` operator on your `Args` object).

# Errors and default values

- If you try to readout a named parameter that doesn't exist an `Args::NoSuchArgException` is thrown.
The exception is not thrown if you define a default value for a named parameter:

```c++
int main(int argc, char* argv[])
{
	Args args(argc, argv);

	std::string kind = args("kind", "dog"); // Default value is string "dog"
	int nLegs = args("nLegs", 4); // Default value is integer 4
	bool isMale = args("isMale", true); // Default value is boolean true
	try
	{
		double weight = args("weight");
		std::string name = args("name");
	}
	catch (const Args::NoSuchArgException& e) // If there was no parameter named 'weight' or 'name'
	{
		std::cerr << e.what() << std::endl;
	}
	/* . . . */
```

- If you run out of parameters in a chained `>>` readout, an `Args::NoMoreArgException` is thrown.

```c++
int main(int argc, char* argv[])
{
	Args args(argc, argv);

	std::string kind;
	int nLegs;
	double weight;
	bool isMale;
	try
	{
		args >> kind >> nLegs >> weight >> isMale;
	}
	catch (const Args::NoMoreArgException& e) // Command-line parameters were fewer than 4
	{
		std::cerr << e.what() << std::endl;
	}
	/* . . . */
```

- If you try to readout a parameter that cannot be parsed considering the type of your variable, a `std::runtime_error`
is thrown. Like `Args::NoSuchArgException` and `Args::NoMoreArgException`, `std::runtime_error` derives from
abstract standard class `std::exception` and can therefore be caught as such. The associated message can be obtained
using the `what()` method in the exception.

# Other features

- The `count()` method of the `Args` object returns the number of (parameter, value) pairs in the command-line.
- The `progName` string attribute of the `Args` object contains the name of the program called in the command-line.
- The `cmdStr()` method of the `Args` object returns a normalized representation of the command-line.
