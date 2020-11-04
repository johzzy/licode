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
#include "pc/SDPReceiver.h"
#include <MediaStream.h>

using namespace erizo;

std::string publisherid = "0";
int main() {

  // new Test();

  SDPReceiver *receiver = new SDPReceiver();
  Observer *subscriber = new Observer("subscriber", receiver);
  Observer *publisher = new Observer("publisher", receiver);
  subscriber->wait();
  publisher->wait();
  return 0;
}

SDPReceiver::SDPReceiver() {
  thread_pool = std::make_unique<erizo::ThreadPool>(5);
  io_thread_pool = std::make_unique<erizo::IOThreadPool>(1);
  muxer = std::make_shared<erizo::OneToManyProcessor>();
}

bool SDPReceiver::createPublisher(std::string peer_id) {
  if (!muxer->getPublisher()) {
    printf("Adding publisher peer_id %s\n", peer_id.c_str());

    erizo::IceConfig iceConfig;
    // iceConfig.turn_server = turnServer;
    // iceConfig.turn_port = turnPort;
    // iceConfig.turn_username = turnUsername;
    // iceConfig.turn_pass = turnPass;
    // iceConfig.network_interface = network_interface;
    //
    // iceConfig.stun_server = stunServer;
    // iceConfig.stun_port = stunPort;
    // iceConfig.min_port = minPort;
    // iceConfig.max_port = maxPort;
    // iceConfig.should_trickle = trickle;
    std::vector<erizo::RtpMap> rtp_mappings;
    std::vector<erizo::ExtMap> ext_mappings;
    bool enable_connection_quality_check = true;
    auto connnection = std::make_shared<erizo::WebRtcConnection>(
        thread_pool->getLessUsedWorker(), io_thread_pool->getLessUsedIOWorker(),
        peer_id, iceConfig, rtp_mappings, ext_mappings,
        enable_connection_quality_check, this);
    connnection->init();

    int session_version = 0;
    std::shared_ptr<erizo::MediaSource> media_source =
        std::make_shared<erizo::MediaStream>(thread_pool->getLessUsedWorker(),
                                             connnection, peer_id, peer_id,
                                             true, session_version);

    media_source->setAudioSink(muxer);
    media_source->setVideoSink(muxer);
    media_source->setEventSink(muxer);

    muxer->setPublisher(media_source, peer_id);
    publisherid = peer_id;
  } else {
    printf("PUBLISHER ALREADY SET\n");
    return false;
  }
  return true;
}

bool SDPReceiver::createSubscriber(std::string peer_id) {
  printf("Adding Subscriber peerid %s\n", peer_id.c_str());
  if (!muxer->getSubscriber(peer_id)) {

    erizo::IceConfig iceConfig;
    // iceConfig.turn_server = turnServer;
    // iceConfig.turn_port = turnPort;
    // iceConfig.turn_username = turnUsername;
    // iceConfig.turn_pass = turnPass;
    // iceConfig.network_interface = network_interface;
    //
    // iceConfig.stun_server = stunServer;
    // iceConfig.stun_port = stunPort;
    // iceConfig.min_port = minPort;
    // iceConfig.max_port = maxPort;
    // iceConfig.should_trickle = trickle;
    std::vector<erizo::RtpMap> rtp_mappings;
    std::vector<erizo::ExtMap> ext_mappings;
    bool enable_connection_quality_check = true;
    auto connnection = std::make_shared<erizo::WebRtcConnection>(
        thread_pool->getLessUsedWorker(), io_thread_pool->getLessUsedIOWorker(),
        peer_id, iceConfig, rtp_mappings, ext_mappings,
        enable_connection_quality_check, this);
    connnection->init();

    int session_version = 0;
    std::shared_ptr<erizo::MediaSink> media_sink =
        std::make_shared<erizo::MediaStream>(thread_pool->getLessUsedWorker(),
                                             connnection, peer_id, peer_id,
                                             true, session_version);
    muxer->addSubscriber(media_sink, peer_id);
  }
  return true;
}

void SDPReceiver::setRemoteSDP(std::string peer_id, const std::string &sdp) {
  if (peer_id == publisherid) {
    // muxer->getPublisher()->setRemoteSdp(sdp);
  } else {
    // muxer->getSubscriber(peer_id)->setRemoteSdp(sdp);
  }
}
std::string SDPReceiver::getLocalSDP(std::string peer_id) {
  std::string sdp;
  if (peer_id == publisherid) {
    // sdp = muxer->getPublisher()->getLocalSdp();
    // sdp = muxer->getPublisher()->
  } else {
    // sdp = muxer->getSubscriber(peer_id)->getLocalSdp();
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
