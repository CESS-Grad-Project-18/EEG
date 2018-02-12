import sklearn
from sklearn import ensemble
import numpy as np
def PredictAndPrint(test_ot,classifier,testlabels_ot,p):
    c =0
    for k in range(len(test_ot)):
        pr = classifier.predict(np.array([test_ot[k]]))
        if(p):
            print("Predicted: ", pr[0], " ,Correct Value: ", testlabels_ot[k] )
        if pr[0] == testlabels_ot[k]:
            c+=1
    print(c, "Correct out of ", len(testlabels_ot)," Percesion: " ,c/len(testlabels_ot)*100 )
    return (c/len(testlabels_ot)*100)

def SVM(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p):
    print("-------------SVM---------------")
    #print(test_ot[0])
    classifier=sklearn.svm.LinearSVC()
    classifier.fit(np.array(data_ot), np.array(labels_ot))
    return PredictAndPrint(test_ot,classifier,testlabels_ot,p)
    

def GaussianNB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p):
    total = ones + twos + threes + fours
    #print(ones/total,twos/total,threes/total,fours/total)
    probs = [ones/total,twos/total,threes/total,fours/total]
    print("------Guasian Naive Bayes--------")
    #print(test_ot[0])
    classifier=sklearn.naive_bayes.GaussianNB()
    classifier.fit(np.array(data_ot), np.array(labels_ot))
    return PredictAndPrint(test_ot,classifier,testlabels_ot,p)

def MultinomialNB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p):
    total = ones + twos + threes + fours
    #print(ones/total,twos/total,threes/total,fours/total)
    probs = [ones/total,twos/total,threes/total,fours/total]
    print("------Multinomial Naive Bayes--------")
    #print(test_ot[0])
    classifier=sklearn.naive_bayes.MultinomialNB()
    classifier.fit(np.array(data_ot), np.array(labels_ot))
    return PredictAndPrint(test_ot,classifier,testlabels_ot,p)

def BernoulliNB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p):
    total = ones + twos + threes + fours
    #print(ones/total,twos/total,threes/total,fours/total)
    probs = [ones/total,twos/total,threes/total,fours/total]
    print("------Bernoulli Naive Bayes--------")
    #print(test_ot[0])
    classifier=sklearn.naive_bayes.BernoulliNB()
    classifier.fit(np.array(data_ot), np.array(labels_ot))
    return PredictAndPrint(test_ot,classifier,testlabels_ot,p)

def Adaboost(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p):
    total = ones + twos + threes + fours
    #print(ones/total,twos/total,threes/total,fours/total)
    probs = [ones/total,twos/total,threes/total,fours/total]
    print("------AdaBoost--------")
    #print(test_ot[0])
    classifier=ensemble.AdaBoostClassifier(learning_rate=0.4)
    classifier.fit(np.array(data_ot), np.array(labels_ot))
    return PredictAndPrint(test_ot,classifier,testlabels_ot,p)

def VotingClassifier(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p):
    total = ones + twos + threes + fours
    #print(ones/total,twos/total,threes/total,fours/total)
    probs = [ones/total,twos/total,threes/total,fours/total]
    print("------VotingClassifier--------")
    #print(test_ot[0])
    clf1 = sklearn.svm.LinearSVC()
    clf2 = ensemble.RandomForestClassifier(random_state=1)
    clf3 = sklearn.naive_bayes.GaussianNB()
    classifier = ensemble.VotingClassifier(estimators=[('lr', clf1), ('rf', clf2), ('gnb', clf3)], voting='hard')
    classifier.fit(np.array(data_ot), np.array(labels_ot))
    return PredictAndPrint(test_ot,classifier,testlabels_ot,p)


def NB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p):
    return GaussianNB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p)
    #MultinomialNB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p)
    return BernoulliNB(data_ot,labels_ot,test_ot,testlabels_ot,ones,twos,threes,fours,p)