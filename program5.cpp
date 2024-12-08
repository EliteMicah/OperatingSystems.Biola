#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
    char source_file[256], destination_file[256];
    int src_off = 0, dst_off = 0;

    // Prompt user for input
    cout << "Enter source file name: ";
    cin >> source_file;
    cout << "Enter destination file name: ";
    cin >> destination_file;

    // Ask for offsets
    cout << "Enter source offset (default 0): ";
    cin >> src_off;
    cout << "Enter destination offset (default 0): ";
    cin >> dst_off;

    // Validate offsets
    if (src_off < 0 || dst_off < 0) {
        cerr << "Error: Offset values must be non-negative integers." << endl;
        return 1;
    }

    // Open source file
    FILE* src = fopen(source_file, "rb");
    if (!src) {
        cerr << "Error: Cannot open source file." << endl;
        return 1;
    }

    // Open destination file
    FILE* dst = fopen(destination_file, "r+b");
    if (!dst) {
        // If the destination file does not exist, create it
        dst = fopen(destination_file, "w+b");
    }
    if (!dst) {
        cerr << "Error: Cannot open or create destination file." << endl;
        fclose(src);
        return 1;
    }

    // Move source file pointer to (src_off + 1)th byte
    if (fseek(src, src_off, SEEK_SET) != 0) {
        cerr << "Error: Source offset is beyond file size." << endl;
        fclose(src);
        fclose(dst);
        return 1;
    }

    // Move destination file pointer to (dst_off + 1)th byte
    if (fseek(dst, dst_off, SEEK_SET) != 0) {
        cerr << "Error: Destination offset is invalid." << endl;
        fclose(src);
        fclose(dst);
        return 1;
    }

    // Copy from source to destination
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dst);
    }

    // Print an error if there is one
    if (ferror(dst)) {
        cerr << "Error: Writing to destination file failed." << endl;
        fclose(src);
        fclose(dst);
        return 1;
    }

    fclose(src);
    fclose(dst);
    cout << "File copied successfully." << endl;

    return 0;
}
