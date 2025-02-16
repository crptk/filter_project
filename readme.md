Based on the extracted files and your description, here’s a **polished README** for your CS50 **Image Filtering Program**:

---

# 🖼️ Image Filtering Program  

## 📌 Overview  
This project is part of my **CS50x coursework** and implements **image filtering functions** in C. It applies **grayscale, blur, edge detection, and flip effects** to **24-bit uncompressed BMP images**.

The core logic is written in `helpers.c`, where I implemented the filtering algorithms. The other files (`helpers.h`, `bmp.h`, `filter.c`, `Makefile`) were provided by the **CS50 staff**.

## 🛠️ How to Compile & Run  
### 🏗️ **Compilation**  
To compile the program, use:  
```bash
make filter
```

### 🚀 **Execution**  
To apply a filter, use:  
```bash
./filter -e/b/g/r images/(inputname).bmp (outputname).bmp
```
- `-e` → **Edge detection**  
- `-b` → **Blur effect**  
- `-g` → **Grayscale**  
- `-r` → **Reverse/Flip**  

### 🔹 Example Usage  
Applying a **blur effect** to `yard.bmp` and saving it as `blurred.bmp`:  
```bash
./filter -b images/yard.bmp images/blurred.bmp
```

## ⚠️ Notes  
- Input images **must be 24-bit uncompressed BMP files**.  
- The program reads an input BMP file, processes it, and writes the **filtered image** to a new file.  
- The **edge detection filter** uses the **Sobel operator** to detect image gradients.  

---

This README provides **clear instructions** while keeping it **concise and professional**. Let me know if you need any refinements! 🚀
