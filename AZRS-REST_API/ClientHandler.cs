// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.SignalR.Client;

namespace Microsoft.Azure.SignalR.Samples.Serverless
{
    public class ClientHandler
    {
        private readonly HubConnection _connection;

        public ClientHandler(string connectionString, string hubName, string userId)
        {
            var serviceUtils = new ServiceUtils(connectionString);

            var url = GetClientUrl(serviceUtils.Endpoint, hubName);
            Console.WriteLine(url);

            _connection = new HubConnectionBuilder()
                .WithUrl(url, option =>
                {
                    option.AccessTokenProvider = () =>
                    {
                        return Task.FromResult(serviceUtils.GenerateAccessToken(url, userId));
                    };
                }).Build();

            _connection.On<RotateArguments>("rotate",
                (arguments) =>
                {
                    //Console.WriteLine($"[{DateTime.Now.ToString()}] Received rotation instruction from server {server}");
                    Console.WriteLine($"[{DateTime.Now.ToString()}] Received rotation instruction: X: {arguments.X}, Y: {arguments.Y}, Z: {arguments.Z}");
                });
        }

        public async Task StartAsync()
        {
            await _connection.StartAsync();
        }

        public async Task DisposeAsync()
        {
            await _connection.DisposeAsync();
        }

        private string GetClientUrl(string endpoint, string hubName)
        {
            return $"{endpoint}/client/?hub={hubName}";
        }
    }
}
