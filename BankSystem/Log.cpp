#include "Log.hpp"

void Log::print(std::ostream& stream) const {
	stream << "[" << time << "] [" <<
		transactTypeToString(transactType) << "] {" << relatedUserId << "} " <<
		description << std::endl;
}

void Log::serialize(std::ostream& stream) const {
	time.serialize(stream);
	serializePrimitive(stream, transactType);
	description.serialize(stream);
	serializePrimitive(stream, relatedUserId);
}

void Log::deserialize(std::istream& stream) {
	time.deserialize(stream);
	deserializePrimitive(stream, transactType);
	description.deserialize(stream);
	deserializePrimitive(stream, relatedUserId);
}

std::ostream& operator<<(std::ostream& stream, const Log& log) {
	log.print(stream);
	return stream;
}