# FJsonMap
A simple way for making HTTP request body strings in Unreal Engine 4

## How to use
Just include the header file that imports `FJsonMap` into scope and then use bracket initialization to create your object like so:
```
FJsonMap RequestBody = {
    { "string", "hello" },
    { "integer", 12 },
    { "boolean", false },
    { "float", 19.4f }
};
```

To to get the JSON string just call the `ToString()` method on the `FJsonMap`
