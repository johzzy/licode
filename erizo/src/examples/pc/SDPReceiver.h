#include <OneToManyProcessor.h>

class SDPReceiver {

public:

	SDPReceiver();
	virtual ~SDPReceiver(){};
	bool createPublisher(std::string peer_id);
	bool createSubscriber(std::string peer_id);
	void setRemoteSDP(std::string peer_id, const std::string &sdp);
	std::string getLocalSDP(std::string peer_id);
	void peerDisconnected(std::string peer_id);

private:

	erizo::OneToManyProcessor* muxer;
};
