#include <iostream>
#include <string>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    std::cout << "=== TEST KẾT NỐI OLLAMA SERVER ===\n\n";
    
    // URL
    const std::string API_URL = "https://dionna-squarelike-centrically.ngrok-free.dev/api/chat";
    
    std::cout << " Đang kết nối tới: " << API_URL << "\n";
    std::cout << " Vui lòng đợi...\n\n";
    
    // Khởi tạo CURL
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    
    if (!curl) {
        std::cerr << " Lỗi: Không thể khởi tạo CURL\n";
        return 1;
    }
    
    // Tạo payload JSON đơn giản
    std::string payload = R"({
        "model": "gpt-oss:20b",
        "messages": [
            {"role": "user", "content": "Hello"}
        ],
        "stream": false
    })";
    
    std::string response;
    
    // Setup CURL
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    
    curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);
    
    // Thực hiện request
    CURLcode res = curl_easy_perform(curl);
    
    // Kiểm tra kết quả
    if (res != CURLE_OK) {
        std::cerr << " LỖI KẾT NỐI: " << curl_easy_strerror(res) << "\n\n";
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return 1;
    }
    
    // Lấy HTTP status code
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    
    std::cout << "📊 HTTP Status Code: " << http_code << "\n\n";
    
    if (http_code == 200) {
        std::cout << " KẾT NỐI THÀNH CÔNG!\n\n";
        std::cout << " Response từ server:\n";
        std::cout << "─────────────────────────────────────\n";
        std::cout << response.substr(0, 500); 
        if (response.length() > 500) {
            std::cout << "...\n";
        } else {
            std::cout << "\n";
        }
        std::cout << "─────────────────────────────────────\n\n";
        std::cout << " Server hoạt động tốt! Có thể chạy chatbot.\n";
    } else {
        std::cout << "  KẾT NỐI KHÔNG THÀNH CÔNG\n\n";
    
    }
    
    // Cleanup
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    
    std::cout << "\n=== KẾT THÚC TEST ===\n";
    
    return (http_code == 200) ? 0 : 1;
}