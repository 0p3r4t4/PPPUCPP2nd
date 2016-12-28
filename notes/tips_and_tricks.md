# Tips and Tricks

## cout/cin streams

### Print bool values as words

The `cout` stream manages output of bool type variables. By default it prints
'1' for true and '0' for false, but we can configure it to write "true" or
"false" with the std::boolalpha modifier.

    bool b = true;
    cout << b;

    output: 1

    bool b = true;
    cout << boolalpha << b;

    output: true

### Apply environment locale

We can instruct `cout` to print in accordance to a certain locale. Or simply in
accordance to the execution environment locale (as opposed to "C" default
locale with):

    cout.imbue(locale(""));

### Modifiers to print out floating-point numbers
        
-   `std::fixed` prints all decimal numbers specified by `std::precision`.

-   `std::defaultfloat` prints the number, honouring `std::precision`,
    in the most convenient format.

        cout << fixed << a << defaultfloat << b << '\n';

### cin state

We can test end of input with `cin.eof()` and input correctness with `cin`:

    while (cin >> var) ...

---

## Misc tips

### Uniform and universal initialization

The _uniform and universal initialization_ through `{}` operator avoids implicit
narrowing conversions:

    double x {2.7};     // OK
    int y {x};          // ERROR: double -> int might narrow
    char b {1000};      // ERROR: literal value produces narrowing

### Random numbers

In a C++11/14 style there is an alternative to classic `srand()` and `rand()`.
In summary, to get random numbers from 0 to 9, you can do something like:

    std::default_random_engine engine(std::time(nullptr));
    std::uniform_int_distribution<> dist(0, 9);
    int r = dist(engine);       // Random value
