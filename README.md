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

## Project Structure

```
ewallet/
├── src/                     # Source code
│   ├── core/               # Application core and entry point
│   ├── services/           # Business logic services
│   ├── repositories/       # Data access layer
│   ├── models/            # Data models and entities
│   ├── ui/                # User interface components
│   └── config/            # Configuration management
├── include/                # Header files (mirrors src structure)
├── build/                  # Compiled object files (auto-generated)
├── data/                   # CSV data files (auto-generated)
├── docs/                   # Documentation
└── Makefile               # Build configuration
```

## Requirements

- **Compiler**: GCC or Clang with C++20 support
- **Operating System**: Linux, macOS, or Windows (with appropriate make utility)
- **Build System**: GNU Make

## Building and Running

### Setup Project Structure
```bash
make setup
```

### Build the Application
```bash
make build
# or simply
make
```

### Run the Application
```bash
make run
```

### Clean Build Files
```bash
make clean          # Remove build files only
make clean-all      # Remove build files and data files
```

### View Help
```bash
make help
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

The application creates CSV files in the `data/` directory:

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

Edit settings in `include/config/Settings.h`:

```cpp
class Settings {
public:
    std::string userRepoType = "InMemory";     // or "FileSystem"
    std::string txRepoType = "InMemory";       // or "FileSystem"
    Language language = Language::English;      // or Language::Deutsch
};
```

## Localization

The application supports English and German languages. Translations are managed in `src/ui/Localizer.cpp`. To add new languages:

1. Add new enum value to `Settings::Language`
2. Add translations to the `initializeTranslations()` method
3. Update language selection menu

## Security Considerations

- Passwords are stored in plain text (suitable for educational purposes only)
- File permissions should be restricted in production environments
- Consider encryption for sensitive data in real-world applications

## Development

### Adding New Features

1. **New Model**: Add to `src/models/` and `include/models/`
2. **New Service**: Add to `src/services/` and `include/services/`
3. **New Repository**: Add to `src/repositories/` and `include/repositories/`
4. **New UI Component**: Add to `src/ui/` and `include/ui/`

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

## Contributing

1. Follow the established directory structure
2. Maintain consistent coding style
3. Update documentation for new features
4. Test thoroughly before submitting changes

## License

This project is created for educational purposes, but not free to modify and distribute as needed except with owner's permission (Mahmoud Sayed - ma7moud111).

## Contact

For questions or contributions, please refer to the project documentation or create an issue in the project repository.
