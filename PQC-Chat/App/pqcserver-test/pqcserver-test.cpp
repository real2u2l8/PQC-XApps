#include <chrono>
#include <iostream>
#include <thread>

#include "tlsserver.h"

struct ChatServer : public TlsServer {
protected:
	void run(Session* session) override {
		std::puts("connected");
		char buf[256];
		while (true) {
			int res = session->read(buf, 256);
			if (res <= 0) break;
			buf[res] = '\0';
			std::puts(buf);
			sessions_.lock();
            for (TlsSession* session: sessions_)
				session->write(buf, res);
			sessions_.unlock();
		}
		std::puts("disconnected");
	}
};

struct Param {
	int port_;

	bool parse(int argc, char** argv) {
		if (argc != 2) return false;
		port_ = std::stoi(argv[1]);
		return true;
	}

	static void usage() {
        printf("syntax : tlsserver-test <port>\n");
        printf("sample : tlsserver-test <port>\n");
	}
};

int main(int argc, char* argv[]) {
	ChatServer cs;

	Param param;
	if (!param.parse(argc, argv)) {
		Param::usage();
		return -1;
    }
    cs.pemFileName_ = "/home/user/project/git/pqc-app/src/crt/rootCA.pem";
            //하드 코딩말고, 꼭 상대 경로로 예쁘게 작성 필요
    if (!cs.start(param.port_)) {
		std::cerr << cs.error_ << std::endl;
		return -1;
	}

	while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	cs.stop();
}
