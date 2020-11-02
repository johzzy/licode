/*
 * hsam.cpp
 */

#include <stdio.h>

#include <OneToManyProcessor.h>
#include <SdpInfo.h>
#include <WebRtcConnection.h>
// #include <LibNiceConnection.h>
// #include <NicerConnection.h>
#include "Test.h"
#include "pc/Observer.h"

using namespace erizo;

std::string publisherid = "0";
int main() {

	new Test();

//	SDPReceiver* receiver = new SDPReceiver();
//	Observer *subscriber = new Observer("subscriber", receiver);
//	new Observer("publisher", receiver);
//	subscriber->wait();
//	return 0;
}

SDPReceiver::SDPReceiver() {
	muxer = new erizo::OneToManyProcessor();
}

bool SDPReceiver::createPublisher(std::string peer_id) {
	if (muxer->getPublisher() == NULL) {
		printf("Adding publisher peer_id %s\n", peer_id.c_str());
		WebRtcConnection *newConn = new WebRtcConnection;
		newConn->init();
		newConn->setAudioReceiver(muxer);
		newConn->setVideoReceiver(muxer);
		muxer->setPublisher(newConn);
		publisherid = peer_id;
	} else {
		printf("PUBLISHER ALREADY SET\n");
		return false;
	}
	return true;
}
bool SDPReceiver::createSubscriber(std::string peer_id) {
	printf("Adding Subscriber peerid %s\n", peer_id.c_str());
	if (muxer->subscribers.find(peer_id) != muxer->subscribers.end()) {
		printf("OFFER AGAIN\n");
		return false;
	}

	WebRtcConnection *newConn = new WebRtcConnection;
	newConn->init();
	muxer->addSubscriber(newConn, peer_id);
	return true;
}
void SDPReceiver::setRemoteSDP(std::string peer_id, const std::string &sdp) {
	if (peer_id == publisherid) {
		muxer->getPublisher()->setRemoteSdp(sdp);
	} else {
		muxer->getSubscriber(peer_id)->setRemoteSdp(sdp);
	}
}
std::string SDPReceiver::getLocalSDP(std::string peer_id) {
	std::string sdp;
	if (peer_id == publisherid) {
		sdp = muxer->getPublisher()->getLocalSdp();
	} else {
		sdp = muxer->getSubscriber(peer_id)->getLocalSdp();
	}
	printf("Getting localSDP %s\n", sdp.c_str());
	return sdp;
}
void SDPReceiver::peerDisconnected(std::string peer_id) {
	if (peer_id != publisherid) {
		printf("removing peer %s\n", peer_id.c_str());
		muxer->removeSubscriber(peer_id);
	}
}

