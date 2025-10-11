#ifndef ENVIRONMENT_ERROR_TESTS_H
#define ENVIRONMENT_ERROR_TESTS_H

#include <gtest/gtest.h>
#include <stdexcept>
#include "Environment.h"

class EnvironmentErrorTest : public ::testing::Test {
protected:
    void SetUp() override {
        env = std::make_unique<Environment>();
    }
    
    void TearDown() override {
        env.reset();
    }
    
    std::unique_ptr<Environment> env;
};

// Error and Exception Handling Tests
TEST_F(EnvironmentErrorTest, InvalidSpawnParameters) {
    // Test error handling for invalid spawn parameters
    EXPECT_THROW(env->spawnEnemy(""), std::invalid_argument);
    
    // Test that valid parameters don't throw
    EXPECT_NO_THROW(env->spawnEnemy("Goblin"));
}

TEST_F(EnvironmentErrorTest, NullEntityHandling) {
    // Test that methods handle null entities gracefully
    EXPECT_NO_THROW(env->removeEntity(nullptr));
    EXPECT_NO_THROW(env->checkCollisions(nullptr));
    
    std::shared_ptr<Entity> nullEntity;
    EXPECT_NO_THROW(env->getEntitiesNear(sf::Vector2f(0, 0), 100.0f));
}

TEST_F(EnvironmentErrorTest, ExtremePositionValues) {
    // Test with extreme position values
    sf::Vector2f extremePos(std::numeric_limits<float>::max(), 
                           std::numeric_limits<float>::lowest());
    
    EXPECT_NO_THROW(env->clampPosition(extremePos, 10.0f));
    EXPECT_NO_THROW(env->getEntitiesNear(extremePos, 100.0f));
}

TEST_F(EnvironmentErrorTest, InvalidRadiusValues) {
    // Test with invalid radius values
    sf::Vector2f pos(400, 300);
    
    EXPECT_NO_THROW(env->clampPosition(pos, -10.0f)); // Negative radius
    EXPECT_NO_THROW(env->clampPosition(pos, 0.0f));   // Zero radius
    EXPECT_NO_THROW(env->clampPosition(pos, 1000.0f)); // Very large radius
    
    EXPECT_NO_THROW(env->getRandomEdgeSpawnPosition(-5.0f));
    EXPECT_NO_THROW(env->getRandomEdgeSpawnPosition(0.0f));
}

TEST_F(EnvironmentErrorTest, LineOfSightEdgeCases) {
    // Test line of sight with edge cases
    sf::Vector2f samePoint(100, 100);
    EXPECT_NO_THROW(env->hasLineOfSight(samePoint, samePoint));
    
    sf::Vector2f invalidPoint(std::numeric_limits<float>::quiet_NaN(), 100);
    EXPECT_NO_THROW(env->hasLineOfSight(sf::Vector2f(0, 0), invalidPoint));
}

TEST_F(EnvironmentErrorTest, MemoryManagementErrors) {
    // Test scenarios that might cause memory issues
    for (int i = 0; i < 1000; ++i) {
        EXPECT_NO_THROW({
            env->addObstacle(sf::FloatRect(i * 10.0f, i * 10.0f, 10.0f, 10.0f));
        });
    }
    
    EXPECT_NO_THROW(env->clearObstacles());
}

TEST_F(EnvironmentErrorTest, UpdateWithLargeDeltaTime) {
    // Test update with various delta time values
    EXPECT_NO_THROW(env->update(0.0f));     // Zero delta time
    EXPECT_NO_THROW(env->update(1.0f));     // Normal delta time
    EXPECT_NO_THROW(env->update(10.0f));    // Large delta time
    EXPECT_NO_THROW(env->update(-1.0f));    // Negative delta time (should be handled)
}

#endif // ENVIRONMENT_ERROR_TESTS_H