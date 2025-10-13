# MOS Legendary Static Crypt

A secure system for embedding encrypted macOS executables as byte arrays and executing them at runtime with automatic decryption.

## Components

### 1. Software (`software/`)
- **hello_world.c**: A simple "Hello World" program
- **Makefile**: Builds the executable

### 2. Packager (`packager/`)
- **packager.py**: Converts macOS executables to encrypted C byte arrays
- Encrypts executables using XOR encryption with configurable password
- Updates `software.h` header file in the runtime directory

### 3. Runtime (`runtime/`)
- **runtime.c**: Decrypts and executes embedded binaries
- **software.h**: Auto-generated header containing encrypted executable bytes
- **Makefile**: Builds the runtime executable

## Usage

### Quick Start
```bash
./build.sh
```

### Manual Build Process

1. **Build the software**:
   ```bash
   cd software
   make
   ```

2. **Package the executable**:
   ```bash
   cd ../packager
   python3 packager.py ../software/hello_world -o ../runtime/software.h
   ```

3. **Build the runtime**:
   ```bash
   cd ../runtime
   make
   ```

4. **Run the system**:
   ```bash
   ./runtime
   ```

### Packager Usage
```bash
python3 packager.py <executable_path> [-o output_header.h] [-p password]
```

**Encryption Options:**
- `-p, --password`: Set encryption password (default: "mos-legendary-crypt-2024")
- The packager encrypts the executable using XOR encryption for security

## How It Works

1. The **software** component is a standard C program that gets compiled to a macOS executable
2. The **packager** reads the executable file, encrypts it using XOR encryption, and converts it to a C byte array
3. The **runtime** program includes the generated header and executes the embedded binary by:
   - Decrypting the byte array using the same password
   - Writing the decrypted data to a temporary file
   - Making it executable
   - Running it via `system()`
   - Cleaning up the temporary file and clearing decrypted data from memory

## File Structure
```
mos-legendary-static-crypt/
├── software/
│   ├── hello_world.c
│   └── Makefile
├── packager/
│   └── packager.py
├── runtime/
│   ├── runtime.c
│   ├── software.h (auto-generated)
│   └── Makefile
├── build.sh
└── README.md
```
