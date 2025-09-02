#include "Localizer.h"

Localizer::Localizer(Settings& s) : settings(s) {
    initializeTranslations();
}

void Localizer::initializeTranslations() {

    translations["register_option"] = {
        {Settings::Language::English, "(R) Register"},
        {Settings::Language::Deutsch, "(R) Registrieren"}
    };
    translations["enter_new_username"] = {
        {Settings::Language::English, "Enter new username: "},
        {Settings::Language::Deutsch, "Neuen Benutzernamen eingeben: "}
    };
    translations["enter_new_password"] = {
        {Settings::Language::English, "Enter new password: "},
        {Settings::Language::Deutsch, "Neues Passwort eingeben: "}
    };
    translations["username_taken"] = {
        {Settings::Language::English, "Username already taken!"},
        {Settings::Language::Deutsch, "Benutzername bereits vergeben!"}
    };
    translations["registration_success"] = {
        {Settings::Language::English, "Registration successful! Logging in..."},
        {Settings::Language::Deutsch, "Registrierung erfolgreich! Anmelden..."}
    };

    // Welcome Menu
    translations["welcome_title"] = {
        {Settings::Language::English, "Welcome to NTI Smart Wallet"},
        {Settings::Language::Deutsch, "Willkommen bei NTI Smart Wallet"}
    };
    translations["login_option"] = {
        {Settings::Language::English, "(L) Login"},
        {Settings::Language::Deutsch, "(L) Anmelden"}
    };
    translations["quit_option"] = {
        {Settings::Language::English, "(Q) Quit"},
        {Settings::Language::Deutsch, "(Q) Beenden"}
    };

    // Login Menu
    translations["enter_username"] = {
        {Settings::Language::English, "Please enter your username: "},
        {Settings::Language::Deutsch, "Bitte geben Sie Ihren Benutzernamen ein: "}
    };
    translations["enter_password"] = {
        {Settings::Language::English, "Please enter your password: "},
        {Settings::Language::Deutsch, "Bitte geben Sie Ihr Passwort ein: "}
    };
    translations["login_success"] = {
        {Settings::Language::English, "Logged in Successfully!"},
        {Settings::Language::Deutsch, "Erfolgreich angemeldet!"}
    };
    translations["invalid_credentials"] = {
        {Settings::Language::English, "Invalid credentials!"},
        {Settings::Language::Deutsch, "Ungültige Anmeldeinformationen!"}
    };
    translations["retry_option"] = {
        {Settings::Language::English, "(R) Retry"},
        {Settings::Language::Deutsch, "(R) Wiederholen"}
    };

    // Options Menu
    translations["options_title"] = {
        {Settings::Language::English, "Please choose a service:"},
        {Settings::Language::Deutsch, "Bitte wählen Sie einen Dienst:"}
    };
    translations["account_statement"] = {
        {Settings::Language::English, "(1) Check Account Statement"},
        {Settings::Language::Deutsch, "(1) Kontostand prüfen"}
    };
    translations["check_balance"] = {
        {Settings::Language::English, "(2) Check Balance"},
        {Settings::Language::Deutsch, "(2) Kontostand überprüfen"}
    };
    translations["transactions_option"] = {
        {Settings::Language::English, "(3) Transactions"},
        {Settings::Language::Deutsch, "(3) Transaktionen"}
    };
    translations["logout_option"] = {
        {Settings::Language::English, "(4) Logout"},
        {Settings::Language::Deutsch, "(4) Abmelden"}
    };

    // Transaction Menu
    translations["transaction_title"] = {
        {Settings::Language::English, "Transaction Menu:"},
        {Settings::Language::Deutsch, "Transaktionsmenü:"}
    };
    translations["show_history"] = {
        {Settings::Language::English, "(1) Show Transaction History"},
        {Settings::Language::Deutsch, "(1) Transaktionsverlauf anzeigen"}
    };
    translations["deposit_option"] = {
        {Settings::Language::English, "(2) Deposit"},
        {Settings::Language::Deutsch, "(2) Einzahlung"}
    };
    translations["withdraw_option"] = {
        {Settings::Language::English, "(3) Withdraw"},
        {Settings::Language::Deutsch, "(3) Abheben"}
    };
    translations["pay_bills"] = {
        {Settings::Language::English, "(4) Pay Bills"},
        {Settings::Language::Deutsch, "(4) Rechnungen bezahlen"}
    };

    // Pay Bills Menu
    translations["pay_bills_title"] = {
        {Settings::Language::English, "Pay Bills Menu:"},
        {Settings::Language::Deutsch, "Rechnungsmenü:"}
    };
    translations["electricity"] = {
        {Settings::Language::English, "(1) Electricity"},
        {Settings::Language::Deutsch, "(1) Strom"}
    };
    translations["water"] = {
        {Settings::Language::English, "(2) Water"},
        {Settings::Language::Deutsch, "(2) Wasser"}
    };
    translations["gas"] = {
        {Settings::Language::English, "(3) Gas"},
        {Settings::Language::Deutsch, "(3) Gas"}
    };

    // Common
    translations["invalid_option"] = {
        {Settings::Language::English, "Invalid option!"},
        {Settings::Language::Deutsch, "Ungültige Option!"}
    };
    translations["back_option"] = {
        {Settings::Language::English, "(B) Back"},
        {Settings::Language::Deutsch, "(B) Zurück"}
    };
    translations["confirm"] = {
        {Settings::Language::English, "(C) Confirm"},
        {Settings::Language::Deutsch, "(C) Bestätigen"}
    };
    translations["main_menu"] = {
        {Settings::Language::English, "(M) Back to Main Menu"},
        {Settings::Language::Deutsch, "(M) Zurück zum Hauptmenü"}
    };
    translations["amount_prompt"] = {
        {Settings::Language::English, "Enter amount to "},
        {Settings::Language::Deutsch, "Geben Sie den Betrag ein zum "}
    };
    translations["bill_amount"] = {
        {Settings::Language::English, "Enter "},
        {Settings::Language::Deutsch, "Geben Sie "}
    };
    translations["bill_amount_suffix"] = {
        {Settings::Language::English, " bill amount: "},
        {Settings::Language::Deutsch, " Rechnungsbetrag ein: "}
    };
    translations["transaction_details_prompt"] = {
        {Settings::Language::English, "Do you want to view details of a specific transaction? (Y/N): "},
        {Settings::Language::Deutsch, "Möchten Sie Details einer bestimmten Transaktion anzeigen? (J/N): "}
    };
    translations["transaction_number_prompt"] = {
        {Settings::Language::English, "Enter transaction number (1-"},
        {Settings::Language::Deutsch, "Geben Sie die Transaktionsnummer ein (1-"}
    };
    translations["invalid_number"] = {
        {Settings::Language::English, "Invalid number.\n"},
        {Settings::Language::Deutsch, "Ungültige Zahl.\n"}
    };
    translations["invalid_transaction"] = {
        {Settings::Language::English, "Invalid transaction number.\n"},
        {Settings::Language::Deutsch, "Ungültige Transaktionsnummer.\n"}
    };
}

std::string Localizer::get(const std::string& key) const {
    auto it = translations.find(key);
    if (it != translations.end()) {
        auto langIt = it->second.find(settings.language);
        if (langIt != it->second.end()) {
            return langIt->second;
        }
    }
    return key; // Fallback to key if translation not found
}