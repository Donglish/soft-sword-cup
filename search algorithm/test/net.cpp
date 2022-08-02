

#include <iostream>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;
int main() {

    // 创建一个监听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        cout << " create listen socket error " << endl;
        return -1;
    }
    // 初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    if (bind(listenfd, (struct sockaddr *)& bindaddr, sizeof(bindaddr)) == -1) {
        cout << "bind listen socket error" << endl;
        return -1;
    }
    // 启动监听
    if (listen(listenfd, SOMAXCONN) == -1) {
        cout << "listen error" << endl;
        return -1;
    }

    while (true) {
        // 创建一个临时的客户端socket
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        // 接受客户端连接
        int clientfd = accept(listenfd, (struct sockaddr *)& clientaddr, &clientaddrlen);
        if (clientfd != -1) {
            char recvBuf[32] = {0};
            // 从客户端接受数据
            int ret = recv(clientfd, recvBuf, 32, 0);
            if (ret > 0) {
                cout << "recv data from cilent , data:" << recvBuf << endl;
                // 将接收到的数据原封不动地发给客户端
                ret = send(clientfd, recvBuf, strlen(recvBuf), 0);
                if (ret != strlen(recvBuf)) {
                    cout << "send data error" << endl;
                } else {
                    cout << "send data to client successfully, data " << recvBuf <<endl;
                }
            } else {
                cout << "recv data error" <<endl;
            }
            close(clientfd);
        }
    }

    // 关闭监听socket
    close(listenfd);
    return 0;
}

