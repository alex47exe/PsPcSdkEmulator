/* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, you can obtain one at
 * https://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2025 Lander Gallastegi (LNDF)
 */

#include "utils.h"

#include <string.h>
#include <fstream>

bool strendswith(const char* str, const char* suffix) {
    if (!str || !suffix) return false;
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);
    if (suffix_len > str_len) return false;
    return strcmp(str + str_len - suffix_len, suffix) == 0;
}

bool wstrendswith(const wchar_t* str, const wchar_t* suffix) {
    if (!str || !suffix) return false;
    size_t str_len = wcslen(str);
    size_t suffix_len = wcslen(suffix);
    if (suffix_len > str_len) return false;
    return wcscmp(str + str_len - suffix_len, suffix) == 0;
}

bool ismemzero(void* ptr, size_t size) {
    uint8_t* p = (uint8_t*)ptr;
    for (size_t i = 0; i < size; ++i) {
        if (p[i] != 0) return false;
    }
    return true;
}

// INI file reading utilities
std::wstring GetModulePath(HMODULE hModule) {
    wchar_t path[MAX_PATH] = { 0 };
    GetModuleFileNameW(hModule, path, MAX_PATH);
    
    // Get the directory part of the path
    wchar_t* lastSlash = wcsrchr(path, L'\\');
    if (lastSlash) {
        *(lastSlash + 1) = L'\0';
    }
    
    return std::wstring(path);
}

std::string GetIniFilePath() {
    // Get the directory and name of the current module
    std::wstring modulePath = GetModulePath(nullptr);
    wchar_t fullPath[MAX_PATH] = { 0 };
    GetModuleFileNameW(nullptr, fullPath, MAX_PATH);
    
    // Extract the filename from the path
    wchar_t* fileName = wcsrchr(fullPath, L'\\');
    fileName = fileName ? fileName + 1 : fullPath;
    
    // Convert wide string filename to narrow string
    char fileNameA[MAX_PATH] = { 0 };
    WideCharToMultiByte(CP_ACP, 0, fileName, -1, fileNameA, MAX_PATH, NULL, NULL);
    
    // Convert wide string path to narrow string
    char path[MAX_PATH] = { 0 };
    WideCharToMultiByte(CP_ACP, 0, modulePath.c_str(), -1, path, MAX_PATH, NULL, NULL);
    
    // Get base name without extension
    std::string baseName = fileNameA;
    size_t extPos = baseName.rfind(".dll");
    if (extPos != std::string::npos) {
        baseName = baseName.substr(0, extPos);
    }
    
    // If the base name is empty or not one of our expected DLLs, use default names
    if (baseName.empty() || 
        (baseName != "PsPcSdkEmulator" && 
         baseName != "PsPcSdkEmu")) {
        // Try to use one of the default names
        if (GetFileAttributesA((std::string(path) + "PsPcSdkEmulator.dll").c_str()) != INVALID_FILE_ATTRIBUTES) {
            baseName = "PsPcSdkEmulator";
        } else if (GetFileAttributesA((std::string(path) + "PsPcSdkEmu.dll").c_str()) != INVALID_FILE_ATTRIBUTES) {
            baseName = "PsPcSdkEmu";
        } else {
            // Default to PsPcSdkEmulator if nothing is found
            baseName = "PsPcSdkEmulator";
        }
    }
    
    // Append .ini extension
    std::string result(path);
    result += baseName + ".ini";
    
    return result;
}

bool CreateDefaultIniFile(const std::string& iniPath) {
    // Check if file already exists
    std::ifstream checkFile(iniPath);
    if (checkFile.good()) {
        checkFile.close();
        return true; // File already exists
    }

    // Extract the base name for messages
    std::string baseName = iniPath;
    size_t lastSlash = baseName.rfind('\\');
    if (lastSlash != std::string::npos) {
        baseName = baseName.substr(lastSlash + 1);
    }
    size_t dotPos = baseName.rfind('.');
    if (dotPos != std::string::npos) {
        baseName = baseName.substr(0, dotPos);
    }

    // Create a new INI file with default values and comments
    std::ofstream iniFile(iniPath);
    if (!iniFile.is_open()) {
        printf("[PsPcSdkEmulator] Failed to create INI file at: %s\n", iniPath.c_str());
        return false;
    }

    iniFile << "; " << baseName << " Configuration File\n";
    iniFile << "; This file is automatically generated if it doesn't exist\n";
    iniFile << "; Customize these settings to change the PSN user details\n\n";
    
    iniFile << "[PSN]\n";
    iniFile << "; PSN ID - Enter a hexadecimal value (default: 0x1234567890ABCDEF)\n";
    iniFile << "; The value can be entered with or without the '0x' prefix\n";
    iniFile << "; Examples: 0x1234567890ABCDEF or 1234567890ABCDEF\n";
    iniFile << "psn_id=0x1234567890ABCDEF\n\n";
    
    iniFile << "; PSN Username - Enter your desired PSN username (default: Player)\n";
    iniFile << "psn_user=Player\n";

    iniFile.close();
    printf("[PsPcSdkEmulator] Created default INI file at: %s\n", iniPath.c_str());
    return true;
}

std::optional<std::string> ReadIniValue(const std::string& iniPath, const char* section, const char* key, const char* defaultValue) {
    // Create default INI file if it doesn't exist
    CreateDefaultIniFile(iniPath);
    
    char buffer[256] = { 0 };
    DWORD result = GetPrivateProfileStringA(section, key, defaultValue ? defaultValue : "", buffer, sizeof(buffer), iniPath.c_str());
    
    if (result == 0 && !defaultValue) {
        return std::nullopt;
    }
    
    return std::string(buffer);
}

std::optional<uint64_t> ReadIniHexValue(const std::string& iniPath, const char* section, const char* key, uint64_t defaultValue) {
    // Create default INI file if it doesn't exist
    CreateDefaultIniFile(iniPath);
    
    char buffer[256] = { 0 };
    DWORD result = GetPrivateProfileStringA(section, key, "", buffer, sizeof(buffer), iniPath.c_str());
    
    if (result == 0) {
        return defaultValue;
    }
    
    // Try to parse as hex
    uint64_t value = 0;
    if (sscanf_s(buffer, "0x%llx", &value) == 1 || 
        sscanf_s(buffer, "%llx", &value) == 1) {
        return value;
    }
    
    return defaultValue;
}
