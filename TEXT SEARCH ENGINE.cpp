/*
 * Universal File Content Search Tool
 * Search any text-based file for specific content
 * Code hints and optimizations by artlest
 * Compatible with all standard C++ compilers and online IDEs
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

// Function to display professional application header
void display_application_header() {
    // You implement a universal file search interface header
    std::cout << "==========================================\n";
    std::cout << "    UNIVERSAL FILE SEARCH UTILITY\n";
    std::cout << "==========================================\n";
    std::cout << "Search any text file for specific content\n";
    std::cout << "Supports: .txt, .cpp, .h, .py, .js, .html, .css, .xml, .json, .md, .log\n";
    std::cout << "Type 'exit' to quit the application\n\n";
}

// Function to check if file exists and is accessible
bool validate_file_accessibility(const std::string& file_path) {
    // You verify the file exists and can be opened for reading
    std::ifstream test_file(file_path);
    
    if (!test_file.is_open()) {
        std::cout << "Error: Cannot access file '" << file_path << "'\n";
        std::cout << "Please check:\n";
        std::cout << "  - File path is correct\n";
        std::cout << "  - File exists in the specified location\n";
        std::cout << "  - You have read permissions\n\n";
        return false;
    }
    
    test_file.close();
    return true; // You confirm successful file validation
}

// Function to determine if file is a supported text format
bool verify_text_file_format(const std::string& file_path) {
    // You extract the file extension for format validation
    size_t extension_position = file_path.find_last_of(".");
    
    if (extension_position == std::string::npos) {
        // You handle files without extensions as potential text files
        return true;
    }
    
    // You convert extension to lowercase for comparison
    std::string file_extension = file_path.substr(extension_position);
    std::transform(file_extension.begin(), file_extension.end(), 
                  file_extension.begin(), ::tolower);
    
    // You define supported text file extensions
    std::vector<std::string> supported_extensions = {
        ".txt", ".cpp", ".c", ".h", ".hpp", ".py", ".js", ".html", 
        ".htm", ".css", ".xml", ".json", ".md", ".log", ".cfg", 
        ".ini", ".yaml", ".yml", ".sql", ".sh", ".bat", ".cs", 
        ".java", ".php", ".rb", ".go", ".rs", ".swift"
    };
    
    // You check if the file extension is in the supported list
    for (const std::string& supported_ext : supported_extensions) {
        if (file_extension == supported_ext) {
            return true; // You confirm supported file format
        }
    }
    
    std::cout << "Warning: '" << file_extension << "' may not be a text file format.\n";
    std::cout << "Attempting to search anyway...\n\n";
    return true; // You allow searching of unknown formats
}

// Function to search for text within a specific file with enhanced results
std::vector<std::string> search_file_content(const std::string& file_path, 
                                           const std::string& search_term,
                                           bool show_context = false) {
    // You initialize the results container for matching lines
    std::vector<std::string> matching_results;
    std::ifstream input_file(file_path);
    
    // You verify file accessibility before processing
    if (!input_file.is_open()) {
        return matching_results;
    }
    
    std::string current_line;
    std::string previous_line = "";
    std::string next_line = "";
    int line_number = 1;
    int match_counter = 0;
    
    // You read all lines into memory for context search capability
    std::vector<std::string> all_file_lines;
    while (std::getline(input_file, current_line)) {
        all_file_lines.push_back(current_line);
    }
    input_file.close();
    
    // You process each line for search term matching with context
    for (int line_index = 0; line_index < all_file_lines.size(); line_index++) {
        current_line = all_file_lines[line_index];
        
        // You convert both search term and line to lowercase for case-insensitive search
        std::string lowercase_line = current_line;
        std::string lowercase_search = search_term;
        
        std::transform(lowercase_line.begin(), lowercase_line.end(), 
                      lowercase_line.begin(), ::tolower);
        std::transform(lowercase_search.begin(), lowercase_search.end(), 
                      lowercase_search.begin(), ::tolower);
        
        // You check if the current line contains the search term
        if (lowercase_line.find(lowercase_search) != std::string::npos) {
            match_counter++;
            
            // You format the basic result with line number and content
            std::stringstream result_formatter;
            result_formatter << "Match " << match_counter << " - Line " << (line_index + 1) 
                           << ": " << current_line;
            
            // You add context lines if requested and available
            if (show_context) {
                if (line_index > 0) {
                    result_formatter << "\n    Context Before: " << all_file_lines[line_index - 1];
                }
                if (line_index < all_file_lines.size() - 1) {
                    result_formatter << "\n    Context After:  " << all_file_lines[line_index + 1];
                }
                result_formatter << "\n";
            }
            
            matching_results.push_back(result_formatter.str());
        }
    }
    
    return matching_results; // You return all matching results with context
}

// Function to get file information and statistics
void display_file_information(const std::string& file_path) {
    // You gather and display comprehensive file statistics
    std::ifstream file_stream(file_path);
    
    if (!file_stream.is_open()) {
        return; // You exit if file cannot be accessed
    }
    
    std::string current_line;
    int total_line_count = 0;
    int total_character_count = 0;
    int total_word_count = 0;
    
    // You calculate file statistics while reading
    while (std::getline(file_stream, current_line)) {
        total_line_count++;
        total_character_count += current_line.length();
        
        // You count words by splitting on whitespace
        std::stringstream word_counter(current_line);
        std::string individual_word;
        while (word_counter >> individual_word) {
            total_word_count++;
        }
    }
    
    file_stream.close();
    
    // You display comprehensive file information
    std::cout << "File Information:\n";
    std::cout << "  Path: " << file_path << "\n";
    std::cout << "  Lines: " << total_line_count << "\n";
    std::cout << "  Words: " << total_word_count << "\n";
    std::cout << "  Characters: " << total_character_count << "\n\n";
}

// Function to execute search operation on specified file
void execute_file_search(const std::string& file_path, const std::string& search_query, 
                        bool include_context = false) {
    // You validate file accessibility before searching
    if (!validate_file_accessibility(file_path)) {
        return; // You exit if file validation fails
    }
    
    // You verify the file format is suitable for text search
    if (!verify_text_file_format(file_path)) {
        return; // You exit if format validation fails
    }
    
    // You display file information for user reference
    display_file_information(file_path);
    
    std::cout << "Searching for: \"" << search_query << "\"\n";
    std::cout << "==========================================\n";
    
    // You execute the search operation with optional context
    std::vector<std::string> search_results = search_file_content(file_path, search_query, include_context);
    
    // You process and display search results
    if (search_results.empty()) {
        std::cout << "No matches found for \"" << search_query << "\" in the specified file.\n";
    } else {
        std::cout << "Found " << search_results.size() << " match(es):\n\n";
        
        // You display each search result with proper formatting
        for (const std::string& result : search_results) {
            std::cout << result << "\n";
            std::cout << "------------------------------------------\n";
        }
    }
    
    std::cout << "==========================================\n\n";
}

// Function to validate user input parameters
bool validate_search_input(const std::string& user_input) {
    // You check if the input string is empty
    if (user_input.empty()) {
        std::cout << "Error: Search term cannot be empty. Please try again.\n\n";
        return false;
    }
    
    // You verify the input is not just whitespace
    if (user_input.find_first_not_of(" \t\n\r") == std::string::npos) {
        std::cout << "Error: Search term contains only whitespace. Please try again.\n\n";
        return false;
    }
    
    return true; // You confirm successful input validation
}

// Function to display comprehensive usage instructions
void display_usage_instructions() {
    // You provide detailed instructions for universal file searching
    std::cout << "Universal File Search Instructions:\n";
    std::cout << "==========================================\n";
    std::cout << "1. Enter the complete file path (e.g., 'document.txt' or 'C:\\\\folder\\\\file.txt')\n";
    std::cout << "2. Enter your search term when prompted\n";
    std::cout << "3. Choose whether to include context lines (y/n)\n\n";
    
    std::cout << "Supported File Types:\n";
    std::cout << "  Text: .txt, .log, .md, .cfg, .ini\n";
    std::cout << "  Programming: .cpp, .c, .h, .py, .js, .java, .cs, .php\n";
    std::cout << "  Web: .html, .css, .xml, .json, .yaml\n";
    std::cout << "  Scripts: .sh, .bat, .sql\n\n";
    
    std::cout << "Search Features:\n";
    std::cout << "  - Case-insensitive matching\n";
    std::cout << "  - Partial word matching\n";
    std::cout << "  - Line context display option\n";
    std::cout << "  - Match counting and statistics\n\n";
    
    std::cout << "Commands:\n";
    std::cout << "  'help' - Show these instructions\n";
    std::cout << "  'exit' - Quit the application\n\n";
}

// Function to handle the main interactive search session
void run_universal_search_session() {
    // You initialize the universal search interface
    std::string target_file_path;
    std::string search_term;
    std::string context_option;
    int search_session_counter = 0;
    
    display_usage_instructions();
    
    // You continue the search loop until user chooses to exit
    while (true) {
        std::cout << "Enter file path (or 'help'/'exit'): ";
        std::getline(std::cin, target_file_path);
        
        // You check for exit command
        if (target_file_path == "exit" || target_file_path == "EXIT") {
            std::cout << "\nUniversal search session terminated successfully.\n";
            std::cout << "Total files searched: " << search_session_counter << "\n";
            break;
        }
        
        // You check for help command
        if (target_file_path == "help" || target_file_path == "HELP") {
            display_usage_instructions();
            continue;
        }
        
        // You validate the file path input
        if (target_file_path.empty()) {
            std::cout << "Error: File path cannot be empty.\n\n";
            continue;
        }
        
        // You prompt for search term
        std::cout << "Enter search term: ";
        std::getline(std::cin, search_term);
        
        // You validate the search input
        if (!validate_search_input(search_term)) {
            continue;
        }
        
        // You prompt for context display option
        std::cout << "Include context lines? (y/n): ";
        std::getline(std::cin, context_option);
        
        bool show_context = (context_option == "y" || context_option == "Y" || 
                           context_option == "yes" || context_option == "YES");
        
        // You execute the universal file search
        execute_file_search(target_file_path, search_term, show_context);
        search_session_counter++;
        
        std::cout << "Search another file or type 'exit' to quit.\n\n";
    }
}

// Main execution function for universal file search application
int main() {
    // You initialize the universal file search application
    display_application_header();
    
    // You start the interactive search session
    run_universal_search_session();
    
    // You display successful program completion
    std::cout << "\n==========================================\n";
    std::cout << "Universal file search utility closed successfully.\n";
    std::cout << "All operations completed without errors.\n";
    std::cout << "Program termination: SUCCESS\n";
    std::cout << "==========================================\n";
    
    return 0; // You return success status to the operating system
}