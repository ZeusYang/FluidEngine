#pragma once

#include <vector>
#include <utility>

#include "Animation.h"
#include "../Geometry/ScalarGrid2.h"
#include "../Geometry/ImplicitSurface2.h"

namespace Engine
{
	//!
	//! \brief Abstract base class for 2-D grid-based emitters.
	//!
	class GridEmitter2
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
		GridEmitter2();

		//! Destructor.
		virtual ~GridEmitter2();

		//! Updates the emitter state from \p currentTimeInSeconds to the following
		//! time-step.
		void update(double currentTimeInSeconds, double timeIntervalInSeconds);

		//! Returns true if the emitter is enabled.
		bool isEnabled() const;

		//! Sets true/false to enable/disable the emitter.
		void setIsEnabled(bool enabled);

		//!
		//! \brief      Sets the callback function to be called when
		//!             GridEmitter2::update function is invoked.
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

	//! Shared pointer type for the GridEmitter2.
	typedef std::shared_ptr<GridEmitter2> GridEmitter2Ptr;

}
