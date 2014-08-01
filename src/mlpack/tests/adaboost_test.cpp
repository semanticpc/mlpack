/**
 * @file Adaboost_test.cpp
 * @author Udit Saxena
 *
 * Tests for Adaboost class.
 */

#include <mlpack/core.hpp>
#include <mlpack/methods/adaboost/adaboost.hpp>

#include <boost/test/unit_test.hpp>
#include "old_boost_test_definitions.hpp"

using namespace mlpack;
using namespace arma;
using namespace mlpack::adaboost;

BOOST_AUTO_TEST_SUITE(AdaboostTest);

/**
 *  This test case runs the Adaboost.mh algorithm on the UCI Iris dataset.
 *  It checks whether the hamming loss breaches the upperbound, which
 *  is provided by ztAccumulator.
 */
BOOST_AUTO_TEST_CASE(HammingLossBoundIris)
{
  arma::mat inputData;

  if (!data::Load("iris.txt", inputData))
    BOOST_FAIL("Cannot load test dataset iris.txt!");

  arma::Mat<size_t> labels;

  if (!data::Load("iris_labels.txt",labels))
    BOOST_FAIL("Cannot load labels for iris iris_labels.txt");
  
  // no need to map the labels here

  // Define your own weak learner, perceptron in this case.
  // Run the perceptron for perceptron_iter iterations.
  int perceptron_iter = 400;

  perceptron::Perceptron<> p(inputData, labels.row(0), perceptron_iter);

  // Define parameters for the adaboost
  int iterations = 100;
  double tolerance = 1e-10;
  Adaboost<> a(inputData, labels.row(0), iterations, tolerance, p);
  int countError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != a.finalHypothesis(i))
      countError++;
  double hammingLoss = (double) countError / labels.n_cols;

  BOOST_REQUIRE(hammingLoss <= a.ztAccumulator);
}

/**
 *  This test case runs the Adaboost.mh algorithm on the UCI Iris dataset.
 *  It checks if the error returned by running a single instance of the 
 *  weak learner is worse than running the boosted weak learner using 
 *  adaboost.
 */
BOOST_AUTO_TEST_CASE(WeakLearnerErrorIris)
{
  arma::mat inputData;

  if (!data::Load("iris.txt", inputData))
    BOOST_FAIL("Cannot load test dataset iris.txt!");

  arma::Mat<size_t> labels;

  if (!data::Load("iris_labels.txt",labels))
    BOOST_FAIL("Cannot load labels for iris iris_labels.txt");
  
  // no need to map the labels here

  // Define your own weak learner, perceptron in this case.
  // Run the perceptron for perceptron_iter iterations.
  int perceptron_iter = 400;

  arma::Row<size_t> perceptronPrediction(labels.n_cols);
  perceptron::Perceptron<> p(inputData, labels.row(0), perceptron_iter);
  p.Classify(inputData, perceptronPrediction);
  
  int countWeakLearnerError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != perceptronPrediction(i))
      countWeakLearnerError++;
  double weakLearnerErrorRate = (double) countWeakLearnerError / labels.n_cols;

  // Define parameters for the adaboost
  int iterations = 100;
  double tolerance = 1e-10;
  Adaboost<> a(inputData, labels.row(0), iterations, tolerance, p);
  int countError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != a.finalHypothesis(i))
      countError++;
  double error = (double) countError / labels.n_cols;

  BOOST_REQUIRE(error <= weakLearnerErrorRate);
}

/**
 *  This test case runs the Adaboost.mh algorithm on the UCI Vertebral 
 *  Column dataset.
 *  It checks whether the hamming loss breaches the upperbound, which
 *  is provided by ztAccumulator.
 */
BOOST_AUTO_TEST_CASE(HammingLossBoundVertebralColumn)
{
  arma::mat inputData;

  if (!data::Load("vc2.txt", inputData))
    BOOST_FAIL("Cannot load test dataset vc2.txt!");

  arma::Mat<size_t> labels;

  if (!data::Load("vc2_labels.txt",labels))
    BOOST_FAIL("Cannot load labels for vc2_labels.txt");
  
  // no need to map the labels here

  // Define your own weak learner, perceptron in this case.
  // Run the perceptron for perceptron_iter iterations.
  int perceptron_iter = 800;

  perceptron::Perceptron<> p(inputData, labels.row(0), perceptron_iter);

  // Define parameters for the adaboost
  int iterations = 50;
  double tolerance = 1e-10;
  Adaboost<> a(inputData, labels.row(0), iterations, tolerance, p);
  int countError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != a.finalHypothesis(i))
      countError++;
  double hammingLoss = (double) countError / labels.n_cols;

  BOOST_REQUIRE(hammingLoss <= a.ztAccumulator);
}

/**
 *  This test case runs the Adaboost.mh algorithm on the UCI Vertebral 
 *  Column dataset.
 *  It checks if the error returned by running a single instance of the 
 *  weak learner is worse than running the boosted weak learner using 
 *  adaboost.
 */
BOOST_AUTO_TEST_CASE(WeakLearnerErrorVertebralColumn)
{
  arma::mat inputData;

  if (!data::Load("vc2.txt", inputData))
    BOOST_FAIL("Cannot load test dataset vc2.txt!");

  arma::Mat<size_t> labels;

  if (!data::Load("vc2_labels.txt",labels))
    BOOST_FAIL("Cannot load labels for vc2_labels.txt");
  
  // no need to map the labels here

  // Define your own weak learner, perceptron in this case.
  // Run the perceptron for perceptron_iter iterations.
  int perceptron_iter = 800;

  arma::Row<size_t> perceptronPrediction(labels.n_cols);
  perceptron::Perceptron<> p(inputData, labels.row(0), perceptron_iter);
  p.Classify(inputData, perceptronPrediction);
  
  int countWeakLearnerError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != perceptronPrediction(i))
      countWeakLearnerError++;
  double weakLearnerErrorRate = (double) countWeakLearnerError / labels.n_cols;

  // Define parameters for the adaboost
  int iterations = 50;
  double tolerance = 1e-10;
  Adaboost<> a(inputData, labels.row(0), iterations, tolerance, p);
  int countError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != a.finalHypothesis(i))
      countError++;
  double error = (double) countError / labels.n_cols;
  
  BOOST_REQUIRE(error <= weakLearnerErrorRate);
}

/**
 *  This test case runs the Adaboost.mh algorithm on non-linearly 
 *  separable dataset. 
 *  It checks whether the hamming loss breaches the upperbound, which
 *  is provided by ztAccumulator.
 */
BOOST_AUTO_TEST_CASE(HammingLossBoundNonLinearSepData)
{
  arma::mat inputData;

  if (!data::Load("nonlinsepdata.txt", inputData))
    BOOST_FAIL("Cannot load test dataset nonlinsepdata.txt!");

  arma::Mat<size_t> labels;

  if (!data::Load("nonlinsepdata_labels.txt",labels))
    BOOST_FAIL("Cannot load labels for nonlinsepdata_labels.txt");
  
  // no need to map the labels here

  // Define your own weak learner, perceptron in this case.
  // Run the perceptron for perceptron_iter iterations.
  int perceptron_iter = 800;

  perceptron::Perceptron<> p(inputData, labels.row(0), perceptron_iter);

  // Define parameters for the adaboost
  int iterations = 50;
  double tolerance = 1e-10;
  Adaboost<> a(inputData, labels.row(0), iterations, tolerance, p);
  int countError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != a.finalHypothesis(i))
      countError++;
  double hammingLoss = (double) countError / labels.n_cols;

  BOOST_REQUIRE(hammingLoss <= a.ztAccumulator);
}

/**
 *  This test case runs the Adaboost.mh algorithm on a non-linearly 
 *  separable dataset. 
 *  It checks if the error returned by running a single instance of the 
 *  weak learner is worse than running the boosted weak learner using 
 *  adaboost.
 */
BOOST_AUTO_TEST_CASE(WeakLearnerErrorNonLinearSepData)
{
  arma::mat inputData;

  if (!data::Load("nonlinsepdata.txt", inputData))
    BOOST_FAIL("Cannot load test dataset nonlinsepdata.txt!");

  arma::Mat<size_t> labels;

  if (!data::Load("nonlinsepdata_labels.txt",labels))
    BOOST_FAIL("Cannot load labels for nonlinsepdata_labels.txt");
  
  // no need to map the labels here

  // Define your own weak learner, perceptron in this case.
  // Run the perceptron for perceptron_iter iterations.
  int perceptron_iter = 800;

  arma::Row<size_t> perceptronPrediction(labels.n_cols);
  perceptron::Perceptron<> p(inputData, labels.row(0), perceptron_iter);
  p.Classify(inputData, perceptronPrediction);
  
  int countWeakLearnerError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != perceptronPrediction(i))
      countWeakLearnerError++;
  double weakLearnerErrorRate = (double) countWeakLearnerError / labels.n_cols;

  // Define parameters for the adaboost
  int iterations = 50;
  double tolerance = 1e-10;
  Adaboost<> a(inputData, labels.row(0), iterations, tolerance, p);
  int countError = 0;
  for (size_t i = 0; i < labels.n_cols; i++)
    if(labels(i) != a.finalHypothesis(i))
      countError++;
  double error = (double) countError / labels.n_cols;
  
  BOOST_REQUIRE(error <= weakLearnerErrorRate);
}
BOOST_AUTO_TEST_SUITE_END();