// 9.exercise.04.cpp
//
//  Look at the headache-inducing last example of §8.4. Indent it properly and
//  explain the meaning of the construct. Note that the example doesn't do
//  anything meaningful; it is pure obfuscation.
//
//  COMMENTS

int maint()
try 
{
    return 0;
}
catch(exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch(...)
{
    cerr << "Unknown exception!\n";
    return 2;
}
