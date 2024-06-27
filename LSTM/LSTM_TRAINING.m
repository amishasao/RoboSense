Dropping1 = load('Dropping 1.txt');
csvwrite('Dropping 1.txt', Dropping1);
Dropping2 = load('Dropping 2.txt');
csvwrite('Dropping 2.txt', Dropping2);
Dropping3 = load('Dropping 3.txt');
csvwrite('Dropping 3.txt', Dropping3);
Picking1 = load('Picking 1.txt');
csvwrite('Picking 1.txt', Picking1);
Picking2 = load('Picking 2.txt');
csvwrite('Picking 2.txt', Picking2);
Picking3 = load('Picking 3.txt');
csvwrite('Picking 3.txt', Picking3);

motorAngles = [];

% Assuming motorAngles is a matrix where each column represents a motor angle
normalizedMotorAngles = normalize(motorAngles);

labels = [];

% Assuming you have already normalized your data

% Define the sequence length
seqLength = 3;  % You can adjust this value based on your data and problem.

% Initialize empty arrays to store sequences and labels
sequences = [];
sequenceLabels = [];

% Calculate the total number of sequences
numSequences = size(normalizedMotorAngles, 1) - seqLength + 1;

% Create sequences
for i = 1:numSequences
    % Extract a sequence of motor angle data
    motorAnglesSeq = normalizedMotorAngles(i:i+seqLength-1, :);

    % Extract the label for this sequence (e.g., the label at the end of the sequence)
    label = labels(i+seqLength-1);

    % Append the sequence to the arrays
    sequences = [sequences; motorAnglesSeq];

    % Append the label to the labels array
    sequenceLabels = [sequenceLabels; label];
end

cellArray = cell(size(sequences, 1), 1);

% Loop to convert each row of the matrix into a row vector and store it in the cell array
for i = 1:size(sequences, 1)
    cellArray{i} = sequences(i, :);
end

% Create a cell array of labels for each time step
cellArrayLabels = cell(size(sequences, 1), 1);
for i = 1:size(sequences, 1)
    cellArrayLabels{i} = sequenceLabels(ceil(i/3));  % Use your label appropriately
end

charVector = cell2mat(sequenceLabels);
dataCategoricalLabels = categorical(charVector);

c = cell(287, 1);

for i = 1:287
    c{i} = cellArray((i-1)*3 + 1:i*3,1);
end

sequences

cFixed = cell(287, 1);

for i = 1:287
    cFixed{i} = cell(3, 4);
end

cFixed


for i = 1:287
    for j = 1:3
        for k = 1:4
            cFixed{i}{j,k} = sequences((i-1)*3+1,k);
        end
    end
end

numSequences
cFixed

numFeatures = 4;  % Number of features (motor angles)
numHiddenUnits = 100;  % Number of hidden units in the LSTM layer
numClasses = 2;  % Number of classes (0 or 1)

% Define the layers of the LSTM network
layers = [
    sequenceInputLayer(numFeatures) % Input layer for sequences
    lstmLayer(numHiddenUnits)      % LSTM layer with the specified number of hidden units
    fullyConnectedLayer(numClasses) % Fully connected layer for classification
    softmaxLayer                    % Softmax layer for probability distribution
    classificationLayer             % Classification output layer
];

% Define training options
options = trainingOptions('adam', ... % Use the appropriate optimization algorithm (e.g., 'adam')
    'MaxEpochs', 12, ... % Number of training epochs
    'MiniBatchSize', 30, ... % Mini-batch size
    'ValidationData', {cFixed, sequenceLabels}, ... % Validation data
    'Plots', 'training-progress'); % Display training progress

% Train the LSTM network
net = trainNetwork(cFixed, sequenceLabels, layers, options);
