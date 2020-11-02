#pragma once

#include <OneToManyProcessor.h>
#include <thread/IOThreadPool.h>
#include <thread/ThreadPool.h>
#include <WebRtcConnection.h>

class SDPReceiver : public erizo::WebRtcConnectionEventListener {
public:
  void notifyEvent(erizo::WebRTCEvent newEvent, const std::string& message) override {
    // todo
  }
	SDPReceiver();
	virtual ~SDPReceiver(){};
	bool createPublisher(std::string peer_id);
	bool createSubscriber(std::string peer_id);
	void setRemoteSDP(std::string peer_id, const std::string &sdp);
	std::string getLocalSDP(std::string peer_id);
	void peerDisconnected(std::string peer_id);

private:
  std::unique_ptr<erizo::ThreadPool> thread_pool;
  std::unique_ptr<erizo::IOThreadPool> io_thread_pool;
  std::shared_ptr<erizo::OneToManyProcessor> muxer;
};
