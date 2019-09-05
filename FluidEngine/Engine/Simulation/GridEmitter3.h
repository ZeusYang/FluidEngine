#pragma once

#include <vector>
#include <utility>

#include "Animation.h"
#include "../Geometry/ScalarGrid3.h"
#include "../Geometry/ImplicitSurface3.h"

namespace Engine
{
	//!
	//! \brief Abstract base class for 3-D grid-based emitters.
	//!
	class GridEmitter3
	{
	public:
		//!
		//! \brief Callback function type for update calls.
		//!
		//! This type of callback function will take the current time and time
		//! interval in seconds.
		//!
		typedef std::function<void(double, double)> OnBeginUpdateCallback;

		//! Constructs an emitter.
		GridEmitter3();

		//! Destructor.
		virtual ~GridEmitter3();

		//! Updates the emitter state from \p currentTimeInSeconds to the following
		//! time-step.
		void update(double currentTimeInSeconds, double timeIntervalInSeconds);

		//! Returns true if the emitter is enabled.
		bool isEnabled() const;

		//! Sets true/false to enable/disable the emitter.
		void setIsEnabled(bool enabled);

		//!
		//! \brief      Sets the callback function to be called when
		//!             GridEmitter3::update function is invoked.
		//!
		//! The callback function takes current simulation time in seconds unit. Use
		//! this callback to track any motion or state changes related to this
		//! emitter.
		//!
		//! \param[in]  callback The callback function.
		//!
		void setOnBeginUpdateCallback(const OnBeginUpdateCallback& callback);

	protected:
		virtual void onUpdate(double currentTimeInSeconds, double timeIntervalInSeconds) = 0;

	private:
		bool _isEnabled = true;
		OnBeginUpdateCallback _onBeginUpdateCallback;

	};

	//! Shared pointer type for the GridEmitter3.
	typedef std::shared_ptr<GridEmitter3> GridEmitter3Ptr;

}
