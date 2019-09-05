#include "ParticleSystemData3.h"

#include <vector>
#include <algorithm>

#include "Timer.h"
#include "PointParallelHashGridSearcher3.h"

namespace Engine
{
	static const size_t kDefaultHashGridResolution = 256;

	ParticleSystemData3::ParticleSystemData3() : ParticleSystemData3(0) { }

	ParticleSystemData3::ParticleSystemData3(size_t numberOfParticles) 
	{
		// Use PointParallelHashGridSearcher3 by default
		_neighborSearcher = std::make_shared<PointParallelHashGridSearcher3>(
			kDefaultHashGridResolution, kDefaultHashGridResolution, kDefaultHashGridResolution, 2.0 * _radius);

		resize(numberOfParticles);
	}

	ParticleSystemData3::ParticleSystemData3(const ParticleSystemData3& other) { set(other); }

	ParticleSystemData3::~ParticleSystemData3() { }

	void ParticleSystemData3::resize(size_t newNumberOfParticles) 
	{
		_numberOfParticles = newNumberOfParticles;
		_positions.resize(_numberOfParticles);
		_velocities.resize(_numberOfParticles);
		_forces.resize(_numberOfParticles);

		for (auto& attr : _scalarDataList) 
			attr.resize(newNumberOfParticles, 0.0);

		for (auto& attr : _vectorDataList) 
			attr.resize(newNumberOfParticles, Vector3D());
	}

	size_t ParticleSystemData3::numberOfParticles() const { return _numberOfParticles; }

	size_t ParticleSystemData3::addScalarData(double initialVal) 
	{
		size_t attrIdx = _scalarDataList.size();
		_scalarDataList.emplace_back(numberOfParticles(), initialVal);
		return attrIdx;
	}

	size_t ParticleSystemData3::addVectorData(const Vector3D& initialVal) 
	{
		size_t attrIdx = _vectorDataList.size();
		_vectorDataList.emplace_back(numberOfParticles(), initialVal);
		return attrIdx;
	}

	double ParticleSystemData3::radius() const { return _radius; }

	void ParticleSystemData3::setRadius(double newRadius) { _radius = std::max(newRadius, 0.0); }

	double ParticleSystemData3::mass() const { return _mass; }

	void ParticleSystemData3::setMass(double newMass) { _mass = std::max(newMass, 0.0); }

	ConstArrayAccessor1<Vector3D> ParticleSystemData3::positions() const { return _positions.constAccessor(); }

	ArrayAccessor1<Vector3D> ParticleSystemData3::positions() { return _positions.accessor(); }

	ConstArrayAccessor1<Vector3D> ParticleSystemData3::velocities() const { return _velocities.constAccessor(); }

	ArrayAccessor1<Vector3D> ParticleSystemData3::velocities() { return _velocities.accessor(); }

	ConstArrayAccessor1<Vector3D> ParticleSystemData3::forces() const { return _forces.constAccessor(); }

	ArrayAccessor1<Vector3D> ParticleSystemData3::forces() { return _forces.accessor(); }

	ConstArrayAccessor1<double> ParticleSystemData3::scalarDataAt(size_t idx) const 
	{
		return _scalarDataList[idx].constAccessor();
	}

	ArrayAccessor1<double> ParticleSystemData3::scalarDataAt(size_t idx) 
	{
		return _scalarDataList[idx].accessor();
	}

	ConstArrayAccessor1<Vector3D> ParticleSystemData3::vectorDataAt(size_t idx) const 
	{
		return _vectorDataList[idx].constAccessor();
	}

	ArrayAccessor1<Vector3D> ParticleSystemData3::vectorDataAt(size_t idx) {
		return _vectorDataList[idx].accessor();
	}

	void ParticleSystemData3::addParticle(
		const Vector3D& newPosition,
		const Vector3D& newVelocity,
		const Vector3D& newForce) 
	{
		Array1<Vector3D> newPositions = { newPosition };
		Array1<Vector3D> newVelocities = { newVelocity };
		Array1<Vector3D> newForces = { newForce };

		addParticles(
			newPositions.constAccessor(),
			newVelocities.constAccessor(),
			newForces.constAccessor());
	}

	void ParticleSystemData3::addParticles(
		const ConstArrayAccessor1<Vector3D>& newPositions,
		const ConstArrayAccessor1<Vector3D>& newVelocities,
		const ConstArrayAccessor1<Vector3D>& newForces) 
	{
		size_t oldNumberOfParticles = numberOfParticles();
		size_t newNumberOfParticles = oldNumberOfParticles + newPositions.size();
		resize(newNumberOfParticles);
		auto pos = positions();
		auto vel = velocities();
		auto frc = forces();

		parallelFor(kZeroSize, newPositions.size(),
			[&](size_t i) {
			pos[i + oldNumberOfParticles] = newPositions[i]; });

		if (newVelocities.size() > 0) 
			parallelFor(kZeroSize, newPositions.size(),
				[&](size_t i) {
				vel[i + oldNumberOfParticles] = newVelocities[i]; });

		if (newForces.size() > 0) 
			parallelFor(kZeroSize, newPositions.size(),
				[&](size_t i) {
				frc[i + oldNumberOfParticles] = newForces[i]; });
	}

	const PointNeighborSearcher3Ptr& ParticleSystemData3::neighborSearcher() const { return _neighborSearcher; }

	void ParticleSystemData3::setNeighborSearcher(const PointNeighborSearcher3Ptr& newNeighborSearcher) 
	{
		_neighborSearcher = newNeighborSearcher;
	}

	const std::vector<std::vector<size_t>>& ParticleSystemData3::neighborLists() const { return _neighborLists; }

	void ParticleSystemData3::buildNeighborSearcher(double maxSearchRadius) 
	{
		Timer timer;

		// Use PointParallelHashGridSearcher3 by default
		_neighborSearcher = std::make_shared<PointParallelHashGridSearcher3>(
			kDefaultHashGridResolution, kDefaultHashGridResolution, kDefaultHashGridResolution, 2.0 * maxSearchRadius);

		_neighborSearcher->build(positions());

		std::cout << "Building neighbor searcher took: " << timer.durationInSeconds() << " seconds\n";
	}

	void ParticleSystemData3::buildNeighborLists(double maxSearchRadius) 
	{
		Timer timer;

		_neighborLists.resize(numberOfParticles());

		auto points = positions();
		for (size_t i = 0; i < numberOfParticles(); ++i) 
		{
			Vector3D origin = points[i];
			_neighborLists[i].clear();

			_neighborSearcher->forEachNearbyPoint(
				origin,
				maxSearchRadius,
				[&](size_t j, const Vector3D&) {
				if (i != j) 
					_neighborLists[i].push_back(j);
			});
		}

		std::cout << "Building neighbor list took: " << timer.durationInSeconds() << " seconds\n";
	}

	void ParticleSystemData3::set(const ParticleSystemData3& other) {
		_radius = other._radius;
		_mass = other._mass;
		_positions = other._positions;
		_velocities = other._velocities;
		_forces = other._forces;
		_numberOfParticles = other._numberOfParticles;

		for (auto& attr : other._scalarDataList) 
			_scalarDataList.emplace_back(attr);

		for (auto& attr : other._vectorDataList) 
			_vectorDataList.emplace_back(attr);

		_neighborSearcher = other._neighborSearcher->clone();
		_neighborLists = other._neighborLists;
	}

	ParticleSystemData3& ParticleSystemData3::operator=(const ParticleSystemData3& other) 
	{
		set(other);
		return *this;
	}
}