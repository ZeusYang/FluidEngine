#include "ParticleSystemData2.h"

#include <vector>
#include <algorithm>

#include "Timer.h"
#include "PointParallelHashGridSearcher2.h"

namespace Engine
{

	static const size_t kDefaultHashGridResolution = 256;

	ParticleSystemData2::ParticleSystemData2() : ParticleSystemData2(0) {}

	ParticleSystemData2::ParticleSystemData2(size_t numberOfParticles) 
	{
		// Use PointParallelHashGridSearcher2 by default
		_neighborSearcher = std::make_shared<PointParallelHashGridSearcher2>(
			kDefaultHashGridResolution, kDefaultHashGridResolution, 2.0 * _radius);

		resize(numberOfParticles);
	}

	ParticleSystemData2::ParticleSystemData2(const ParticleSystemData2& other) { set(other); }

	ParticleSystemData2::~ParticleSystemData2() { }

	void ParticleSystemData2::resize(size_t newNumberOfParticles) 
	{
		_numberOfParticles = newNumberOfParticles;
		_positions.resize(_numberOfParticles);
		_velocities.resize(_numberOfParticles);
		_forces.resize(_numberOfParticles);

		for (auto& attr : _scalarDataList) 
			attr.resize(newNumberOfParticles, 0.0);

		for (auto& attr : _vectorDataList) 
			attr.resize(newNumberOfParticles, Vector2D());
	}

	size_t ParticleSystemData2::numberOfParticles() const { return _numberOfParticles; }

	size_t ParticleSystemData2::addScalarData(double initialVal) 
	{
		size_t attrIdx = _scalarDataList.size();
		_scalarDataList.emplace_back(numberOfParticles(), initialVal);
		return attrIdx;
	}

	size_t ParticleSystemData2::addVectorData(const Vector2D& initialVal) 
	{
		size_t attrIdx = _vectorDataList.size();
		_vectorDataList.emplace_back(numberOfParticles(), initialVal);
		return attrIdx;
	}

	double ParticleSystemData2::radius() const { return _radius; }

	void ParticleSystemData2::setRadius(double newRadius) { _radius = std::max(newRadius, 0.0); }

	double ParticleSystemData2::mass() const { return _mass; }

	void ParticleSystemData2::setMass(double newMass) { _mass = std::max(newMass, 0.0); }

	ConstArrayAccessor1<Vector2D> ParticleSystemData2::positions() const { return _positions.constAccessor(); }

	ArrayAccessor1<Vector2D> ParticleSystemData2::positions() { return _positions.accessor(); }

	ConstArrayAccessor1<Vector2D> ParticleSystemData2::velocities() const { return _velocities.constAccessor(); }

	ArrayAccessor1<Vector2D> ParticleSystemData2::velocities() { return _velocities.accessor(); }

	ConstArrayAccessor1<Vector2D> ParticleSystemData2::forces() const { return _forces.constAccessor(); }

	ArrayAccessor1<Vector2D> ParticleSystemData2::forces() { return _forces.accessor(); }

	ConstArrayAccessor1<double> ParticleSystemData2::scalarDataAt(size_t idx) const 
	{
		return _scalarDataList[idx].constAccessor();
	}

	ArrayAccessor1<double> ParticleSystemData2::scalarDataAt(size_t idx) 
	{
		return _scalarDataList[idx].accessor();
	}

	ConstArrayAccessor1<Vector2D> ParticleSystemData2::vectorDataAt(size_t idx) const 
	{
		return _vectorDataList[idx].constAccessor();
	}

	ArrayAccessor1<Vector2D> ParticleSystemData2::vectorDataAt(size_t idx) 
	{
		return _vectorDataList[idx].accessor();
	}

	void ParticleSystemData2::addParticle(
		const Vector2D& newPosition,
		const Vector2D& newVelocity,
		const Vector2D& newForce) 
	{
		Array1<Vector2D> newPositions = { newPosition };
		Array1<Vector2D> newVelocities = { newVelocity };
		Array1<Vector2D> newForces = { newForce };

		addParticles(
			newPositions.constAccessor(),
			newVelocities.constAccessor(),
			newForces.constAccessor());
	}

	void ParticleSystemData2::addParticles(
		const ConstArrayAccessor1<Vector2D>& newPositions,
		const ConstArrayAccessor1<Vector2D>& newVelocities,
		const ConstArrayAccessor1<Vector2D>& newForces) 
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

	const PointNeighborSearcher2Ptr& ParticleSystemData2::neighborSearcher() const { return _neighborSearcher; }

	void ParticleSystemData2::setNeighborSearcher(const PointNeighborSearcher2Ptr& newNeighborSearcher) 
	{
		_neighborSearcher = newNeighborSearcher;
	}

	const std::vector<std::vector<size_t>>& ParticleSystemData2::neighborLists() const { return _neighborLists; }

	void ParticleSystemData2::buildNeighborSearcher(double maxSearchRadius) 
	{
		Timer timer;
		// Use PointParallelHashGridSearcher2 by default
		_neighborSearcher = std::make_shared<PointParallelHashGridSearcher2>(
			kDefaultHashGridResolution, kDefaultHashGridResolution, 2.0 * maxSearchRadius);

		_neighborSearcher->build(positions());

		std::cout << "Building neighbor searcher took: " << timer.durationInSeconds() << " seconds\n";
	}

	void ParticleSystemData2::buildNeighborLists(double maxSearchRadius) 
	{
		Timer timer;

		_neighborLists.resize(numberOfParticles());

		auto points = positions();
		for (size_t i = 0; i < numberOfParticles(); ++i) 
		{
			Vector2D origin = points[i];
			_neighborLists[i].clear();

			_neighborSearcher->forEachNearbyPoint(
				origin,
				maxSearchRadius,
				[&](size_t j, const Vector2D&) {
				if (i != j) 
					_neighborLists[i].push_back(j); });
		}

		std::cout << "Building neighbor list took: " << timer.durationInSeconds() << " seconds\n";
	}

	void ParticleSystemData2::set(const ParticleSystemData2& other) {
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

	ParticleSystemData2& ParticleSystemData2::operator=(const ParticleSystemData2& other) 
	{
		set(other);
		return *this;
	}
}