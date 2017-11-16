load s03.mat

%X = reshape(data(1,1,:), 1, 8064);
alpha = [];
beta = [];
delta = [];
theta = [];
gamma = [];
areas = [];
X = reshape(data(1,1,:), 1, 8064);
Fs = 128; %Sample Frequency
Ts = 1/Fs; %Sample Period
dur = 63; %Second
Y = fft(X);
%Y = fftshift(fft(X));
t = (0:Ts:dur-Ts);
N = size(t,2);
mag = abs(Y);
F = Fs/N;
f = -Fs/2:F:Fs/2-F;
%filteredData(data, R_pass, R_stop, W_pass_low, W_pass_high, W_stop_low, W_stop_high)
test_1 = filteredData(referenceDifference(reshape(data(1,:,:), 40, 8064)), 30, 50);
for i=1:1:40
    X1 = reshape(data(i,:,:), 40, 8064);
    X1 = referenceDifference(X1);
    gamma = filteredData(X1, 30, 50);
    alpha = filteredData(X1, 8, 13);
    beta = filteredData(X1, 13, 30);
    theta = filteredData(X1, 4, 8);
    delta = filteredData(X1, 1, 4);
    areas = [areas, abs(getArea(alpha)), abs(getArea(beta)), abs(getArea(delta)), abs(getArea(theta)), abs(getArea(gamma))];
end
areas = reshape(areas, 40, 30);
[idx, cent] = kmeans(areas, 4);
valence_median = median(labels(:,1));
arousal_median = median(labels(:,2));
lbls = labels(:,1:2);
lbls(:,1) = (lbls(:,1) >= valence_median);
lbls(:,2) = (lbls(:,2) >= arousal_median);
%Difference
%Training - testing
%SVMModel = fitcsvm(areas, lbls(:,1), 'KernelFunction','rbf', 'Standardize', true, 'ClassNames', {'0', '1'});
%SVMModel = fitcsvm(areas, lbls(:,1), 'KernelFunction','polynomial', 'Standardize', true, 'ClassNames', {'0', '1'});
SVMModel = fitcsvm(areas(1:30, :), lbls(1:30,1), 'KernelFunction','polynomial', 'Standardize', true, 'ClassNames', {'0', '1'});
%CSVMModel = SVMModel.Trained{1}; % Extract trained, compact classifier
%testInds = test(SVMModel.Partition);   % Extract the test indices
%XTest = X(testInds,:);
%YTest = Y(testInds,:);
%[label,score] = predict(CSVMModel,XTest);
[label,score] = predict(SVMModel,areas(31:40, :));
fprintf("Accuracy is %.3f\n", sum(lbls(31:40, 1) == str2num(cell2mat(label))) * 10)
%table(YTest(1:10),label(1:10),score(1:10,2),'VariableNames',...
%    {'TrueLabel','PredictedLabel','Score'})
%SVM = svmtrain(trainset,class);
%Group = svmclassify(SVMStruct,testset);

%function f_d = filteredData(data, R_pass, R_stop, W_pass_low, W_pass_high, W_stop_low, W_stop_high)
function f_d = filteredData(data, W_pass_low, W_pass_high)
Fs = 128; %Sample Frequency
Y = fft(data);
bp = fdesign.bandpass('Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2', W_pass_low -  0.5, W_pass_low, W_pass_high, W_pass_high + 0.5,40,1,40,128);
W_pass = [W_pass_low, W_pass_high]/(Fs/2); %Frequency bands
%W_stop = [W_stop_low, W_stop_high]/(Fs/2);
W_stop = [W_pass_low - 0.5, W_pass_high + 0.5]/(Fs/2);
%W_pass = [8, 13]/(Fs/2); %Frequency bands
%W_stop = [7.5, 13.5]/(Fs/2);
R_pass = 0.5; %Ripple bands
R_stop = 60;
[n, Wn] = buttord(W_pass,W_stop,R_pass,R_stop);
[z, p, k] = butter(n, Wn, 'bandpass');
[sos, g] = zp2sos(z, p, k);
bp_n = dfilt.df2sos(sos, g);
f_d = filter(bp_n, Y);
end

function val = referenceDifference(data)
val(1,:) = data(1,:) - data(17,:);
val(2,:) = data(2,:) - data(18,:);
val(3,:) = data(3,:) - data(20,:);
val(4,:) = data(4,:) - data(21,:);
val(5,:) = data(5,:) - data(22,:);
val(6,:) = data(6,:) - data(23,:);
end

function area = getArea(channel)
for i=1:1:size(channel,1)
    area(i) = trapz(channel(i,:));
end
end