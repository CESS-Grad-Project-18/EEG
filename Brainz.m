classdef Brainz < matlab.apps.AppBase

    % Properties that correspond to app components
    properties (Access = private)
        Brainy        matlab.ui.Figure
        AlphaBtn      matlab.ui.control.Button
        BetaBtn       matlab.ui.control.Button
        DeltaBtn      matlab.ui.control.Button
        GammaBtn      matlab.ui.control.Button
        ThetaBtn      matlab.ui.control.Button
        AlphaGauge    matlab.ui.control.SemicircularGauge
        BetaGauge     matlab.ui.control.SemicircularGauge
        DeltaGauge    matlab.ui.control.SemicircularGauge
        GammaGauge    matlab.ui.control.SemicircularGauge
        ThetaGauge    matlab.ui.control.SemicircularGauge
        FeelingLabel  matlab.ui.control.Label
        ReadingAxes   matlab.ui.control.UIAxes        
    end


    properties (Access = public)
        AlphaValue = 0 % Value of the Alpha signal recieved
        BetaValue  = 0 % Value of the Beta signal recieved
        DeltaValue = 0 % Value of the Delta signal recieved
        GammaValue = 0 % Value of the Gamma signal recieved
        ThetaValue = 0 % Value of the Theta signal recieved
        Tiva = serial('COM6', 'BaudRate', 9600); % Serial port to Tiva-C
        SignalPlot
    end

    methods (Access = public)
            
    end


    % App initialization and construction
    methods (Access = private)

        % Create UIFigure and components
        function createComponents(app)

            % Create Brainy
            app.Brainy = uifigure;
            app.Brainy.Position = [100 100 640 480];
            app.Brainy.Name = 'How are you feeling';

            % Create AlphaBtn
            app.AlphaBtn = uibutton(app.Brainy, 'push');
            app.AlphaBtn.Icon = 'Beta.png';
            app.AlphaBtn.Position = [160 31 100 22];
            app.AlphaBtn.Text = 'Beta';

            % Create BetaBtn
            app.BetaBtn = uibutton(app.Brainy, 'push');
            app.BetaBtn.Icon = 'Delta.png';
            app.BetaBtn.Position = [281 31 100 22];
            app.BetaBtn.Text = 'Delta';

            % Create DeltaBtn
            app.DeltaBtn = uibutton(app.Brainy, 'push');
            app.DeltaBtn.Icon = 'Alpha.png';
            app.DeltaBtn.Position = [25 31 100 22];
            app.DeltaBtn.Text = 'Alpha';

            % Create GammaBtn
            app.GammaBtn = uibutton(app.Brainy, 'push');
            app.GammaBtn.Icon = 'Gamma.png';
            app.GammaBtn.Position = [409 31 100 22];
            app.GammaBtn.Text = 'Gamma';

            % Create ThetaBtn
            app.ThetaBtn = uibutton(app.Brainy, 'push');
            app.ThetaBtn.Icon = 'Theta.png';
            app.ThetaBtn.Position = [525 31 100 22];
            app.ThetaBtn.Text = 'Theta';

            % Create AlphaGauge
            app.AlphaGauge = uigauge(app.Brainy, 'semicircular');
            app.AlphaGauge.Position = [31 61 89 48];

            % Create BetaGauge
            app.BetaGauge = uigauge(app.Brainy, 'semicircular');
            app.BetaGauge.Position = [166 61 89 48];

            % Create DeltaGauge
            app.DeltaGauge = uigauge(app.Brainy, 'semicircular');
            app.DeltaGauge.Position = [287 61 89 48];

            % Create GammaGauge
            app.GammaGauge = uigauge(app.Brainy, 'semicircular');
            app.GammaGauge.Position = [415 61 89 48];

            % Create ThetaGauge
            app.ThetaGauge = uigauge(app.Brainy, 'semicircular');
            app.ThetaGauge.Position = [531 61 89 48];

            % Create FeelingLabel
            app.FeelingLabel = uilabel(app.Brainy);
            app.FeelingLabel.Position = [91 381 460 80];
            app.FeelingLabel.Text = '';
            
            % Create UIAxes
            app.ReadingAxes = uiaxes(app.Brainy);
            title(app.ReadingAxes, '')
            app.ReadingAxes.Box = 'on';
            app.ReadingAxes.XGrid = 'off';
            app.ReadingAxes.YGrid = 'off';
            app.ReadingAxes.Position = [39 134 549 299];
            set(app.ReadingAxes,'xtick',[],'ytick',[]);
            
            app.SignalPlot = plot(app.ReadingAxes, 0:0.001:pi, sin(0:0.001:pi));
            % set(app.SignalPlot,'XData',[0,1,2],'YData',[1,2,1]) % change the line data
            
            set(app.Tiva, 'DataBits', 8);
            set(app.Tiva, 'StopBits', 1);
            set(app.Tiva, 'Parity', 'none');
            set(app.Tiva, 'BytesAvailableFcnMode', 'byte');
            set(app.Tiva, 'Terminator', 'CR/LF');
            app.Tiva.BytesAvailableFcn = createCallbackFcn(app, @dataAvailable, 'true');
            fopen(app.Tiva);
        end
        
        function dataAvailable(app, src, event)
           bytes = fread(app.Tiva, app.Tiva.BytesAvailable);
           % data = sprintf('%s', bytes);
           % disp(data);
           fprintf('%s\n', bytes)
        end
        
    end

    methods (Access = public)

        % Construct app
        function app = Brainz

            % Create and configure components
            createComponents(app)

            % Register the app with App Designer
            registerApp(app, app.Brainy)

            if nargout == 0
                clear app
            end
        end
        
       function updateView(app)
            app.AlphaGauge.Value = app.AlphaValue;
            app.BetaGauge.Value = int8(app.BetaValue);
            app.DeltaGauge.Value = int8(app.DeltaValue);
            app.GammaGauge.Value = int8(app.GammaValue);
            app.ThetaGauge.Value = int8(app.ThetaValue);
       end
        
       function setPlot(app)
           disp(app.SignalPlot)
       end
       
        function setAlpha(app, value)
            app.AlphaValue = value;
            updateView(app);
        end
        
        function setBeta(app, value)
            app.BetaValue = value;
            updateView(app);
        end
        
        function setDelta(app, value)
            app.DeltaValue = value;
            updateView(app);
        end
        
        function setGamma(app, value)
            app.GammaValue = value;
            updateView(app);
        end
        
        function setTheta(app, value)
            app.ThetaValue = value;
            updateView(app);
        end

        function sendData(app, data)
            fprintf(app.Tiva, char(data));
        end

        % Code that executes before app deletion
        function delete(app)
            fclose(app.Tiva);
            % Delete UIFigure when app is deleted
            delete(app.Brainy)
        end
    end
end