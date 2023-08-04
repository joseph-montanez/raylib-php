#zend_api #functions

## Introduction

Interlacing a C library in PHP isn't that bad when dealing with primitives. Primitives are strings, ints, floats, and bools. Functions are broken up into 3 major components, the function signature, function body, and function return.

The following example can be show of how to pass an integer to a c-api function from another library.

```c
// Set camera pan key to combine with mouse movement (free camera)
// RLAPI void SetCameraPanControl(int keyPan);
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetCameraPanControl, 0, 0, 1)
    ZEND_ARG_INFO(0, keyPan)
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetCameraPanControl)
{
    zend_long keyPan;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(keyPan)
    ZEND_PARSE_PARAMETERS_END();


    SetCameraPanControl((int) keyPan);
}
```

I'll show a break-down of all the parts but its important to know that this is just the tip of the iceburg and there are other things you need to do such as function registering to get the function into your PHP application.

## Argument Declartion
Since PHP 7, argument declaration is needed. This helps with the reflection API and type checks for you. Previously you'd need to check types if you wanted to prevent segment faults from a developer inputing bad data into your function. In the example about I used `ZEND_BEGIN_ARG_INFO_EX` and `ZEND_ARG_INFO` but these are just basic declarations. `ZEND_BEGIN_ARG_INFO_EX` only requires 3 parameters but has 4 with one being used (don't ask me why). Below outlines each parameter's purpose.  

```c
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetCameraPanControl, 0, 0, 1)
//                                   |             |   |  |
//              1. Name Of ArgInfo ---             |   |  |
//              2. (Unused) -----------------------|   |  |
//              3. Referenced Params ----------------  |  |
//              4. Required Params -----------------------|
```

In PHP you can optional and referenced variables. Lets take the following example for how a referenced parameter is written in PHP.

```php
$value = 2;
function SetCameraPanControl(&$value) {
    $value = 23;
}

echo $value; // 2
SetCameraPanControl($value);
echo $value; // 23
```

In this function, this is explicitly overriding the parameter. This is normally called an **out** variable. Its used to return mutliple values. Circling back to the Zend API, if you take that example and want to write it in C, then the following would be defined.

```c
ZEND_BEGIN_ARG_INFO_EX(arginfo_SetCameraPanControl, 0, 1, 1)
//                One total references in function ----|   //
    ZEND_ARG_INFO(1, keyPan)
//                |---- Parameter is marked as "reference" //
ZEND_END_ARG_INFO()
PHP_FUNCTION(SetCameraPanControl)
{
    zval *z_keyPan;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ZVAL(z_keyPan)
    ZEND_PARSE_PARAMETERS_END();


    ZEND_TRY_ASSIGN_REF_LONG(z_keyPan, 23);
}
```

If you've noticed, we can no longer use `Z_PARAM_LONG`, because this is a reference it needs to point to the variable, and not value. This is because we are updating the variable and not the value. This is critical to understand because `zval` is not the actual value, its the variable (reference). So when we give the paramater we pulled in a value, we are assigning the reference, not the value. On top of that each type in PHP has their own assignment macro. 

I am not sure if you've notived but the ALL_CAPS_CALLS() in the C-code are macros in C. A macro writes C-code when compiled. Without the extensive use of macros in the Zend API, you'd been looking at a LOT of cryptic boiler plate code.

Now I've brought up that `ZEND_BEGIN_ARG_INFO_EX` is a basic example. What if you want to have types in your parameters and return types? Well there is a whole host of macros to use with varying usages. Here is a quick example:

```c
ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_INFO_EX(arginfo_SetCameraPanControl, 0, 1, IS_LONG, 1)
//                                                                                       |    |
//                                                                 Return Type ----------|    |
//                                                                 Is Nullable ---------------|
    ZEND_ARG_TYPE_INFO(0, keyPan, IS_LONG, 0)
//                                     |   |
//         Parameter Type -------------|   |
//         Is Nullable --------------------|
ZEND_END_ARG_INFO()
```

This would make the function in PHP look like this:

```php
function SetCameraPanControl(int $keyPan): ?int {
    //... logic here
}
```

Now for internal functions you write in C, there is an understanding of tentative return types. This is because unlike in PHP code, if you specified a return type, it would cause a fatal error. So by making it tentative you avoid this. This is to change in PHP 9, but this is how it works for the time being. Now here is an exhastive list as of PHP 8.1.

```c
#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX2(name, return_reference, required_num_args, class_name, allow_null, is_tentative_return_type)

#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null)
  
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null)
  
#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO(name, class_name, allow_null) 

#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX2(name, return_reference, required_num_args, type, is_tentative_return_type)

#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(name, return_reference, required_num_args, type)  
  
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_MASK_EX(name, return_reference, required_num_args, type) 

#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX2(name, return_reference, required_num_args, class_name, type, is_tentative_return_type)

#define ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(name, return_reference, required_num_args, class_name, type) 
  
#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_OBJ_TYPE_MASK_EX(name, return_reference, required_num_args, class_name, type) 

#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX2(name, return_reference, required_num_args, type, allow_null, is_tentative_return_type)
  
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) 

#define ZEND_BEGIN_ARG_WITH_TENTATIVE_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) 
  
#define ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO(name, type, allow_null) 

#define ZEND_BEGIN_ARG_INFO_EX(name, _unused, return_reference, required_num_args)

#define ZEND_BEGIN_ARG_INFO(name, _unused)

```

Type masks is another topic, beyond nullable. For example in PHP when you have `public string|int $foo = 23;`, the type mask is `string|int`. I'll go into this more later but should give you an idea how much more in-depth you can go with types. Providing this rich information not only helps you write less type-checking code in C, but also provides better a reflection API of for your end-users.