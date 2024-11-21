![[Screenshot 2024-11-21 123846.png]]

### **Common Causes of Runtime Crashes**

1. **Memory Access Violations**
    
    - Accessing memory outside the bounds of arrays or pointers can lead to crashes. For example:
        - Reading or writing beyond the allocated array size.
        - Dereferencing invalid or null pointers.
2. **Stack Overflow**
    
    - Recursive calls or very large local arrays can cause a stack overflow.
3. **Division by Zero**
    
    - Any division operation where the divisor is zero will cause a runtime crash.
4. **Graphics Library-Specific Issue**
    
    - Since you are using `iGraphics`, it's possible that a function call to the library is being used incorrectly (e.g., out-of-range values for drawing functions, uninitialized states, etc.).
5. **Incorrect Cleanup**
    
    - Not properly freeing dynamically allocated memory or relying on uninitialized variables can also cause unexpected behavior.

---

### **Steps to Debug**

1. **Enable Debugging**
    
    - Run your program in **debug mode** (use a debugger in VS Code or your IDE).
    - Add breakpoints and step through the code to find where the crash occurs.
2. **Inspect Array Bounds**
    
    - Check if you're accessing out-of-bounds elements in arrays (e.g., when managing obstacles).
3. **Check `dy` and Position Updates**
    
    - Ensure all computations involving `dy`, `playerX`, `playerY`, and obstacle coordinates are valid.
4. **iGraphics Function Calls**
    
    - Validate the arguments passed to `iGraphics` functions, such as `iRectangle` or `iFilledRectangle`.
5. **Check Terminal Output**
    
    - Add more debugging statements (`printf`) to identify where the error occurs.

---

### **Analyzing the Error Code**

The exit code `-1073740771` (0xC000041D) often indicates an **unhandled exception**:

- This is usually caused by invalid memory operations or improper usage of external libraries.

---

### **Suggested Fixes**

1. **Use Compiler Flags**
    
    - If you're using GCC or similar, compile with `-Wall -Wextra` to catch warnings about potential issues.
2. **Run Static Analysis**
    
    - Use tools like **Valgrind** (if possible) to detect memory leaks or invalid accesses.
3. **Temporary Logging**
    
    - Add print statements before and after critical sections of the code to narrow down the problematic part.
4. **Safe Array Access**
    
    - For arrays like `rec_obs`, ensure you’re not accessing beyond `RecObsNo`:
        
        c
        
        Copy code
        
        `if (i >= 0 && i < RecObsNo) {     // Safe to access rec_obs[i] }`