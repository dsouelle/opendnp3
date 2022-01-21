#ifndef OPENDNP3_FREEZEREQUESTHANDLERADAPTER_H
#define OPENDNP3_FREEZEREQUESTHANDLERADAPTER_H


#include <opendnp3/outstation/FreezeRequestHandler.h>

#include "GlobalRef.h"
#include "LocalRef.h"

#include "../jni/JNIWrappers.h"

class FreezeRequestHandlerAdapter final : public opendnp3::FRHANDLER
{
public:
	FreezeRequestHandlerAdapter(jni::JFRHANDLER proxy) : proxy(proxy) {}

	void ProcessHeader(const opendnp3::AllObjectsHeader& record) override;

	void ProcessHeader(const opendnp3::RangeHeader& header) override;

private:

}

#endif