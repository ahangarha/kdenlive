#include "catch.hpp"
#include <memory>
#define private public
#include "timeline2/model/trackmodel.hpp"
#include "timeline2/model/timelinemodel.hpp"
#include "timeline2/model/clipmodel.hpp"

#include <mlt++/MltProducer.h>
#include <mlt++/MltFactory.h>
#include <mlt++/MltProfile.h>



TEST_CASE("Basic creation/deletion of a track", "[TrackModel]")
{
    std::shared_ptr<TimelineModel> timeline = std::make_shared<TimelineModel>();

    int id1 = TrackModel::construct(timeline);
    REQUIRE(timeline->getTracksCount() == 1);

    int id2 = TrackModel::construct(timeline);
    REQUIRE(timeline->getTracksCount() == 2);

    int id3 = TrackModel::construct(timeline);
    REQUIRE(timeline->getTracksCount() == 3);

    // Test deletion
    timeline->deleteTrackById(id1);
    REQUIRE(timeline->getTracksCount() == 2);

    timeline->deleteTrackById(id2);
    REQUIRE(timeline->getTracksCount() == 1);

    timeline->deleteTrackById(id3);
    REQUIRE(timeline->getTracksCount() == 0);
}



TEST_CASE("Basic creation/deletion of a clip", "[ClipModel]")
{
    std::shared_ptr<TimelineModel> timeline = std::make_shared<TimelineModel>();

    Mlt::Factory::init( NULL );
    Mlt::Profile profile;

    std::shared_ptr<Mlt::Producer> producer = std::make_shared<Mlt::Producer>(profile, "test");
    std::shared_ptr<Mlt::Producer> producer2 = std::make_shared<Mlt::Producer>(profile, "test2");

    REQUIRE(timeline->getClipsCount() == 0);
    int id1 = ClipModel::construct(timeline, producer);
    REQUIRE(timeline->getClipsCount() == 1);

    int id2 = ClipModel::construct(timeline, producer2);
    REQUIRE(timeline->getClipsCount() == 2);

    int id3 = ClipModel::construct(timeline, producer);
    REQUIRE(timeline->getClipsCount() == 3);

    // Test deletion
    timeline->deleteClipById(id2);
    REQUIRE(timeline->getClipsCount() == 2);
    timeline->deleteClipById(id3);
    REQUIRE(timeline->getClipsCount() == 1);
    timeline->deleteClipById(id1);
    REQUIRE(timeline->getClipsCount() == 0);
}