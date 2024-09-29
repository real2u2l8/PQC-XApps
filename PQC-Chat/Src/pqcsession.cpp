#include "pqcsession.h"

TlsSession::TlsSession(int sock, SSL* ssl) {
	sock_ = sock;
	ssl_ = ssl;
}

TlsSession::~TlsSession() {
	close();
}

int TlsSession::read(char* buf, int size) {
	int res = ::SSL_read(ssl_, buf, size);
	if (res == 0 || res == -1) {
		return -1;
	}
	return res;
}

int TlsSession::write(char* buf, int size) {
	int res = ::SSL_write(ssl_, buf, size);
	if (res == 0 || res == -1) {
		return -1;
	}
	return res;
}

bool TlsSession::close() {
	if (ssl_ != nullptr) {
		::SSL_free(ssl_);
		ssl_ = nullptr;
	}
	if (sock_ != 0) {
		::shutdown(sock_, SHUT_RDWR);
		::close(sock_);
		sock_ = 0;
	}
	return true;
}
