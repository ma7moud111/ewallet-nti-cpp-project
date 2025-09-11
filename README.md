# E-Wallet Application

A comprehensive digital wallet application written in C++20 with multi-language support and CSV-based data persistence.

## Features

- **User Management**: Registration, login, and authentication
- **Transaction Operations**: Deposit, withdrawal, bill payments, and money transfers
- **Money Transfers**: Send money to other users in the system
- **Multi-language Support**: English and German localization
- **Data Persistence**: CSV file-based storage for users and transactions
- **Transaction History**: View detailed transaction records
- **Balance Management**: Real-time balance tracking



## Requirements

- **Compiler**: GCC or Clang with C++20 support
- **Operating System**: Linux, macOS, or Windows (with appropriate make utility)
- **Build System**: GNU Make

## Building and Running


### Run the Application
```bash
make run
```

## Usage

1. **Language Selection**: Choose your preferred language (English/German) on startup
2. **Registration/Login**: Create a new account or login with existing credentials
3. **Main Menu**: Access account information, balance checking, and transaction operations
4. **Transactions**: 
   - Deposit money into your account
   - Withdraw money (with balance validation)
   - Transfer money to other users
   - Pay utility bills (electricity, water, gas)
   - View transaction history with detailed information

## Data Files

The application creates CSV files:

- **users.csv**: Stores user credentials (username, password)
- **transactions.csv**: Stores all transaction records with user attribution

### CSV Format

**users.csv**:
```
username,password
alice,password123
bob,mypassword
```

**transactions.csv**:
```
type,amount,description,timestamp,status,username
Deposit,100.00,Deposit transaction,1640995200,Completed,alice
Transfer,25.50,Transfer to bob,1640995300,Completed,alice
Transfer,-25.50,Transfer from alice,1640995300,Completed,bob
```

## Architecture

### Core Components

- **Application**: Main application controller and resource manager
- **MenuManager**: Handles UI navigation and user session management
- **TransactionService**: Business logic for financial operations
- **Repositories**: Data persistence abstraction (in-memory and file-based)

### Design Patterns

- **Repository Pattern**: Abstracts data access with swappable implementations
- **Dependency Injection**: Services receive dependencies through constructors
- **RAII**: Automatic resource management using smart pointers
- **Strategy Pattern**: Different storage strategies (memory vs. file)

## Configuration

Edit settings in `Settings.h`:

```cpp
class Settings {
public:
    std::string userRepoType = "InMemory";     // or "FileSystem"
    std::string txRepoType = "InMemory";       // or "FileSystem"
    Language language = Language::English;      // or Language::Deutsch
};
```

## Localization

The application supports English and German languages. Translations are managed in `Localizer.cpp`. To add new languages:

1. Add new enum value to `Settings::Language`
2. Add translations to the `initializeTranslations()` method
3. Update language selection menu

## Security Considerations

- Passwords are stored in plain text (suitable for educational purposes only)
- File permissions should be restricted in production environments
- Consider encryption for sensitive data in real-world applications


### Testing

Manual testing scenarios:
- User registration with duplicate usernames
- Login with invalid credentials
- Transfer to non-existent users
- Insufficient balance operations
- Transaction history viewing
- Language switching

## Troubleshooting

### Build Issues
- Ensure C++20 compiler support
- Check include paths in source files after reorganization
- Verify all source files are in correct directories

### Runtime Issues
- Check file permissions for CSV files
- Ensure data directory exists
- Verify CSV file format integrity

